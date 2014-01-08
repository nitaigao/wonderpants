MIN = 50
MAX = 280
RATE = 30

function update(delta)
  if not active then return end
  
  local spatial = component:get("spatial")
  
  if spatial.x > MIN and spatial.x > MAX then
    local deltaToMax = MAX - spatial.x
    transform:translate(deltaToMax, 0)
    RATE = -RATE
  end
  
  if spatial.x < MIN and spatial.x < MAX then
    local deltaToMin = MIN - spatial.x
    transform:translate(deltaToMin, 0)
    RATE = -RATE
  end
  
  local inc = RATE * delta
  transform:translate(inc, 0)
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