function on_charge()
  if not active then return end
  active = false
  renderer:fade_out(0.3)
end

function show_finger()
  renderer:play_animation("tutorial_finger", true)
  renderer:fade_in(1)
end

function on_tutorial_finished()
  show_finger()
end

function on_state_changed(state)
  if not active then return end  
  if state == GameState.STATE_LEVEL_START then
    show_finger()
  end
end

function main()
  active = true
  event:register('launchable_charging', on_charge)
  event:register('state_changed', on_state_changed)  
end