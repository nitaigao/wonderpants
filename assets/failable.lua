function on_state_changed(state)
  if not active then return end  
  if state == GameState.STATE_LEVEL_WIN or 
     state == GameState.STATE_LEVEL_LOST then
    active = false
  end
end

function on_hit(source, target, material)
  if not active then return end
  if source == this.label then
    active = false
    event:post('failable_hit', this.label)
  end
end

function main()
  event:register('state_changed', on_state_changed)
  event:register('collision', on_hit)
  active = true
end