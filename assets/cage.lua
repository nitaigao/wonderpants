function on_state_changed(state)
  if state == GameState.STATE_LEVEL_WIN or 
     state == GameState.STATE_LEVEL_LOST and active then
    active = false
  end
end

function on_open_finished()
  entity:destroy()
end

function on_key_collected(pair_id)
  if not active then return end
  if pair_id == this.pair_id then
    active = false
    renderer:play_animation('cage_open', false, false, on_open_finished)
  end
end

function main()
  event:register('state_changed', on_state_changed)
  event:register('cage_key_collected', on_key_collected)
  active = true
end