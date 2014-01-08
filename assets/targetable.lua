function on_state_changed(state)
  if state == GameState.STATE_LEVEL_WIN or 
     state == GameState.STATE_LEVEL_LOST and active then
    active = false
  end
end

function on_hit(source, target, material)
  if active and source == this.label then
    if material == "launchable" then
      active = false
      entity:destroy()
      event:post("targetable_collected")
      sfx:play_effect('level_win')
      sfx:vibrate()   
    end
  end
end

function main()
  event:register('state_changed', on_state_changed)
  event:register('collision', on_hit)
  active = true
end