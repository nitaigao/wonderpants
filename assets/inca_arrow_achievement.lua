require 'maths'

function update_old(dt)
  if not active then return end
  
  local arrow_spatial = component:get('spatial')
  
  -- the update method starts before the components are connected
  if arrow_spatial then
    local arrow_vector = Vector:new({x = arrow_spatial.x, y = arrow_spatial.y})
  
    local darrell_spatial = component:get('spatial', darrell.label)
    local darrell_vector = Vector:new({x = darrell_spatial.x, y = darrell_spatial.y})
  
    local new_distance = arrow_vector:distance(darrell_vector)
  
    if new_distance < closest_distance then
      closest_distance = new_distance
    end
  
    -- idea here is there is a near and then in the next 20 update_olds 
    -- the player is still alive, post the achievement
    timer = timer + 1
    if timer > 20 then 
      timer = 0 
      if closest_distance < 42 then
        event:post("close_shave")
        active = false
      end
    end
  end
end

function on_state_changed(state)
  if state == GameState.STATE_LEVEL_WIN or 
     state == GameState.STATE_LEVEL_LOST then
    active = false
  end
end

function main()
  darrell = nil
  local l = component:get_all("launchable")
  for i, v in ipairs(l) do
    darrell = v
  end
  closest_distance = 10000
  timer = 0    
  active = true
end