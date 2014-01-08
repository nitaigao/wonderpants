rate = 0

function on_state_changed(state)
  if state == GameState.STATE_LEVEL_WIN or 
     state == GameState.STATE_LEVEL_LOST and active then
    active = false
  end
end

function update(dt) 
  if not active then return end
  rotation = (rate * (3.141/180)) * dt; 
  transform:rotate(rotation)
end

function main()
  event:register('state_changed', on_state_changed)
  active = true
end