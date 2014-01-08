MIN = 50
MAX = 280
RATE = 30

function update(delta)
  if not active then return end
  
  local spatial = component:get("spatial")

  if spatial.y <= MIN then
    local difference = MIN - spatial.y
    local nudge_amount = spatial.y + difference
    transform:set_translation(spatial.x, nudge_amount)
    RATE = -RATE
  end
  
  if spatial.y >= MAX then
    local difference = MAX - spatial.y
    local nudge_amount = spatial.y + difference
    transform:set_translation(spatial.x, nudge_amount)
    RATE = -RATE
  end
  
  local inc = RATE * delta    
  local newY = spatial.y + inc
  
  transform:set_translation(spatial.x, newY)
end

function on_state_changed(state)
  if state == GameState.STATE_LEVEL_START then   
    active = true
  end
  
  if state == GameState.STATE_LEVEL_WIN or 
     state == GameState.STATE_LEVEL_LOST and active then
    active = false
  end
end

function main()
  event:register('state_changed', on_state_changed)
end