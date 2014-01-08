require 'table'
require 'maths'
require 'queue'
require 'reset_orientation'

function collect_swing_points()
  local points = component:get_all('swingable')
  for i, swing_point in ipairs(points) do
     local swing_point_spatial = component:get('spatial', swing_point.label)
     local swing_point_position = Vector:new({x=swing_point_spatial.x, y=swing_point_spatial.y})
     
     local point = { 
        position           = swing_point_position,
        label              = swing_point.label,
        LINE_OF_SIGHT_ONLY = swing_point.LINE_OF_SIGHT_ONLY,
        GRAB_RADIUS        = swing_point.GRAB_RADIUS,
        in_circle          = false
      }
     
     table.insert(swing_points,point)
  end
end

function show_possible_points()
  local darrell = component:get("spatial")
  local darrell_vector = Vector:new({x=darrell.x,y=darrell.y})

  local closest_swing_point = get_front_most_swing_point()

  for i, swing_point in ipairs(swing_points) do
  
    local diff = darrell_vector:distance(Vector:new(swing_point.position)) - swing_point.GRAB_RADIUS
  
    if closest_swing_point and swing_point.label == closest_swing_point.label and diff < 0 and swing_point.in_circle == false then
      renderer:fade_in_swing_circle(swing_point.label)
      event:post('swing_point_close', swing_point.label)
      swing_point.in_circle = true
    elseif diff > 0 and swing_point.in_circle then
      event:post('swing_point_far', swing_point.label)
      renderer:fade_out_swing_circle(swing_point.label)
      swing_point.in_circle = false
    end
  end  
end

function update(dt)
  if not active then return end
  
  show_possible_points()  
  if current_swing_point then check_if_stuck() end
end

function check_if_stuck()
  local swing_point_spatial = component:get('spatial', current_swing_point.label)
  local spatial = component:get('spatial')
  local direction = Vector:new({x = swing_point_spatial.x - spatial.x, y = swing_point_spatial.y - spatial.y })

  -- check if pretty much upside down
  if direction.y < 0 then
    local speed = Vector:new({x = spatial.x - spatial.last_x, y = spatial.y - spatial.last_y})
      
    stuck_queue:add(speed:length())
  
    if stuck_queue:max() < 0.05 then 
      stuck_queue:empty()
      disable_claw(true) 
    end
  end
end

function get_swing_point()
  local spatial = component:get('spatial')
  local swing_point = get_front_most_swing_point()
  if not swing_point then return nil end
  
  if swing_point.LINE_OF_SIGHT_ONLY then
    if not is_swing_point_clear(swing_point) then 
      swing_point = nil
    end
  end  
  
  return swing_point
end

function get_front_most_swing_point()
   local spatial = component:get('spatial')
   local position = Vector:new({x=spatial.x, y=spatial.y})
   
   local front_most = nil
   local front_most_distance = 9999

   local last_position = Vector:new({x=spatial.last_x, y=spatial.last_y})

   for i, swing_point in ipairs(swing_points) do
     local distance = (swing_point.position - position):length()
     
     if distance < swing_point.GRAB_RADIUS and distance < front_most_distance then
        front_most_distance = distance
        front_most = swing_point
     end
   end  

   return front_most 
end

function adjust_position_for_grab(swing_point)
  local spatial = component:get('spatial')
  local position = Vector:new({x=spatial.x, y=spatial.y})
  local swing_point_spatial = component:get('spatial',swing_point.label)
  local swing_point_position = Vector:new({x=swing_point_spatial.x, y=swing_point_spatial.y})
  
  local distance = (swing_point_position - position):length()
  local direction = Vector:new({x = spatial.x - swing_point_spatial.x, y = spatial.y - swing_point_spatial.y})
  local direction_unit_vector = direction:normalize_slow()
  
  if distance < minimum_distance then
    local scale_factor = math.sqrt(minimum_distance-distance) * 6 -- arbitary scale amount
    local new_position = direction_unit_vector:scale(scale_factor)
    transform:set_translation(spatial.x + new_position.x, spatial.y + new_position.y)
  end
end

function is_swing_point_clear(swing_point)
  return physics:line_of_sight(this.label, swing_point.label)
end


function enable_claw()
  active_swing_point = get_swing_point()
  if active_swing_point then -- there could be no swing points
    adjust_position_for_grab(active_swing_point)
    claw = true
    gameplay:create_rope(active_swing_point.label, this.label)
    physics:set_shape("dayrll_swinging", this.label)
    renderer:play_animation('swing', true)
    sfx:play_effect('grapple')
    current_swing_point = active_swing_point
    event:post('swing_started', this.label, active_swing_point.label)
    transform:look_at(active_swing_point.label, 10)
    physics:set_linear_dampening(0.05, this.label)
  end  
end

function disable_claw(change_animation)
  claw = false
  gameplay:delete_rope(this.label)
  transform:stop_look_at(active_swing_point.label)
  physics:set_linear_dampening(0, this.label)
  event:post('swing_stopped')
  current_swing_point = nil
  if change_animation then 
    renderer:play_animation('launched', true)
    physics:set_shape("dayrll_roll", this.label)
  end
end

function on_input_started()
  if not active then return end  
  if claw then
    disable_claw(true)
  else 
    enable_claw()
  end
end

function on_state_changed(state)
  if state == GameState.STATE_LEVEL_START then
    collect_swing_points()
  end

  if not active then return end  
  
  if state == GameState.STATE_LEVEL_WIN or state == GameState.STATE_LEVEL_LOST then
    active = false
  end
end

function on_launched(label)
  active = true
end

function on_input_moved(direction, amount)
  if not active then return end 
  if claw then
    movement_direction = Vector:new({x = 1, y = 0})
    if direction == "left" then
      movement_direction = movement_direction:inverse()
    end
    physics:apply_impulse(movement_direction, amount*0.8, this.label)
  end
end

function on_air_fail()
  claw = false
  gameplay:delete_rope(this.label)
  transform:stop_look_at(active_swing_point.label)
  physics:set_linear_dampening(0, this.label)
  event:post('swing_stopped')
  current_swing_point = nil
  reset_orientation()
  renderer:play_animation('missed', true)
  sfx:play_effect('darrell_fail')
end

function on_failable_hit()
  claw = false
  gameplay:delete_rope(this.label)
  transform:stop_look_at(active_swing_point.label)
  physics:set_linear_dampening(0, this.label)
  event:post('swing_stopped')
  current_swing_point = nil
end

function on_hit_target()
  if claw then
    claw = false
    gameplay:delete_rope(this.label)
    transform:stop_look_at(active_swing_point.label)
    event:post('swing_stopped')
  end
  reset_orientation()
end

function on_teleport_enter()
  if claw then
    disable_claw(true)
  end
end

function on_hit(source, target, material)
  if not active then return end
  if source == this.label then
    if (material == nil or material == "") and not claw then
      sfx:play_effect("darrell_collide")
    end    
  end
end

function main()  
  event:register('input_started', on_input_started);
  event:register('input_moved', on_input_moved)
  event:register('state_changed', on_state_changed)
  event:register('launchable_launched', on_launched)
  event:register('air_fail', on_air_fail)
  event:register('failable_hit', on_failable_hit)
  event:register('targetable_collected', on_hit_target)
  event:register('teleport_entrance_hit', on_teleport_enter)
  event:register('collision', on_hit)
  claw = false
  active = false
  swing_points = {}
  minimum_distance = 40
  current_swing_point = nil
  
  stuck_queue = Queue:new({size=20})
  stuck_queue:clear()
end