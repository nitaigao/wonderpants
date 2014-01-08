require 'maths'

WIND_FORCE = 50.0
INFLUENCE_THRESHOLD = 500
INFLUENCE_COLUMN_WIDTH = 100

function inside(launchable_position, spatial, offset, offset_angle)
  local blowable_position = Vector:new({x=spatial.x, y=spatial.y})
  local blow_direction = Vector:new({x=0, y=1})
  local blow_direction_rotated = blow_direction:rotate(-spatial.rotation)

  local local_offset_rotated = offset:rotate(-spatial.rotation)
  local local_launchable_position = blowable_position:inverse() + launchable_position + local_offset_rotated:inverse()
  
  local launchable_angle = degrees(blow_direction_rotated:normalize_fast():angle(local_launchable_position:normalize_fast()))
  local launchable_dot = blow_direction_rotated:rotate(offset_angle):dot(local_launchable_position)
  
  return launchable_dot > 0 and launchable_angle < 90
end

function blow(spatial, launchable_position, label, dt)
  local blowable_position = Vector:new({x=spatial.x, y=spatial.y})
  local distance_to_wind_source = (blowable_position - launchable_position):length()
  if distance_to_wind_source < INFLUENCE_THRESHOLD then
    local influence = (INFLUENCE_THRESHOLD - distance_to_wind_source) / 100
    local force = WIND_FORCE * influence
    local blow_direction = Vector:new({x=0, y=1}):rotate(-spatial.rotation)
    physics:apply_impulse(blow_direction, WIND_FORCE * dt, label)      
  end  
end

function update(dt) 
  if not active then return end
  local spatial = component:get("spatial")
  local l = component:get_all("parachute")
  for i, v in ipairs(l) do
    if v.parachute_active then
      local launchable_spatial = component:get("spatial", v.label)
      local launchable_position = Vector:new({x=launchable_spatial.x, y=launchable_spatial.y})
      
      local influence_zone = Vector:new({x=INFLUENCE_COLUMN_WIDTH / 2, 0})
      local left_result = inside(launchable_position, spatial, -influence_zone, -90)
      local right_result = inside(launchable_position, spatial, influence_zone, 90)
      
      if left_result and right_result then
        blow(spatial, launchable_position, v.label, dt)
      end
    end
  end
end

function on_state_changed(state)
  if state == GameState.STATE_LEVEL_WIN or state == GameState.STATE_LEVEL_LOST then
    active = false
  end
end
function deactivate()
  active = false
end

function main()
  event:register('state_changed', on_state_changed)
  event:register('failable_hit', deactivate)
  active = true
end
