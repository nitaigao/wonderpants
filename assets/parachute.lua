require 'table'
require 'maths'
require 'reset_orientation'
require 'queue'

STEER_STRENGTH = 2.0
SPEED_DAMPENING  = 4
ALLOW_INPUT = true

function enable_parachute()
  if ok_parachute then
    relocate_for_parachute()
    reset_orientation()
    lean_queue:clear()
    physics:set_linear_dampening(SPEED_DAMPENING, this.label)
    renderer:play_animation('parachute', true)
    sfx:play_effect('parachute')
    physics:set_shape("dayrll_parachute", this.label)
    parachute = true
    this.parachute_active = parachute
    event:post("parachute_opened")
  end
end

function disable_parachute()
  physics:set_shape("dayrll_roll", this.label)
  physics:set_linear_dampening(0, this.label)
  parachute = false
  transform:rotate(0)
  this.parachute_active = parachute
end

function relocate_for_parachute()
  local direction = Vector:new({x = 0, y = -1})
  local result = physics:ray_hit_within(direction, 30)
  if result then
    local spatial = component:get('spatial')
    transform:set_translation(spatial.x, spatial.y + offset_amount)
  end
end

function on_input_started()
  if not active then return end 
  if parachute then
    renderer:play_animation('launched', true)
    disable_parachute()
  else
    enable_parachute()
  end
end

PARACHUTE_DEAD_TIME = 0.1

function update(dt)
  if not active then return end
  
  if ok_parachute_time < PARACHUTE_DEAD_TIME then
    ok_parachute_time = ok_parachute_time + dt
    if ok_parachute_time > PARACHUTE_DEAD_TIME then
      ok_parachute = true
    end
  end
  
  if parachute then
    lean_queue:add(0)
    local avg = lean_queue:average() * 10    
    transform:set_rotation(avg)
    local direction = Vector:right()
    physics:apply_force(direction, avg * 25, this.label)
  end
end

function on_input_moved(direction, amount)
  if not active then return end
  if parachute then
    movement_direction = Vector:new({x = 1, y = 0})
    step = 0.03

    if direction == "left" then
      movement_direction = movement_direction:inverse()
      step = -step
    end
    
    lean_queue:add(step)
    physics:apply_impulse(movement_direction, STEER_STRENGTH, this.label)    
  end
end

function on_state_changed(state)
  if not active then return end    
  
  if state == GameState.STATE_LEVEL_WIN or state == GameState.STATE_LEVEL_LOST then
    active = false
  end
end

function on_launched()
  active = true
end

function on_crashed(label)
  if not active then return end  
  if parachute then
    local spatial = component:get('spatial')
    transform:set_translation(spatial.x, spatial.y - offset_amount)
  end
end

function on_bounce(target)
  if target == this.label then
    renderer:play_animation('launched', true)
    disable_parachute()
  end
end

function on_air_fail()
  if parachute then relocate_for_parachute() end
  parachute = false
end

function on_hit(source, target, material)
  if not active then return end
  if source == this.label then
    if (material == nil or material == "") and not parachute then
      sfx:play_effect("darrell_collide")
    end    
  end
end

function on_failable_hit()
  if parachute then disable_parachute() end
end

function main()  
  event:register('input_started', on_input_started)
  event:register('state_changed', on_state_changed)
  event:register('launchable_launched', on_launched)
  event:register('launchable_crashed', on_crashed)
  event:register('bouncable_hit', on_bounce)
  event:register('air_fail', on_air_fail)
  event:register('collision', on_hit)
  event:register('failable_hit', on_failable_hit)
  if ALLOW_INPUT then
    event:register('input_moved', on_input_moved)
  end
  offset_amount = 30
  parachute = false
  this.parachute_active = parachute
  active = false
  lean_queue = Queue:new({size=50})
  lean_queue:clear()
  ok_parachute = false
  ok_parachute_time = 0
end