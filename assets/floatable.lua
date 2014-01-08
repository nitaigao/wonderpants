require 'maths'

SPEED = 3
DISTANCE = 0.2

function increment_float(dt)
  local spatial = component:get('spatial')
 
  local rotated_x = math.cos(angle) * DISTANCE - math.sin(angle) * DISTANCE
  local rotated_y = math.sin(angle) * DISTANCE + math.cos(angle) * DISTANCE

  transform:translate(rotated_x, rotated_y)
  angle = angle + SPEED * dt
end

function update(dt)
  if not active then return end   
  increment_float(dt)
end

function on_state_changed(state)
  if state == GameState.STATE_LEVEL_WIN or 
     state == GameState.STATE_LEVEL_LOST and active then
    active = false
  end
end

function main()
  event:register('state_changed', on_state_changed)
  
  active = true
  angle = 0
  first_run = true
end