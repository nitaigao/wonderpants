function on_state_changed(state)
  if state == GameState.STATE_LEVEL_WIN or 
     state == GameState.STATE_LEVEL_LOST and active then
    active = false
  end
end

function on_hit(source, target, material)
  if active and source == this.label then
    if material == "launchable" then
      event:post('inca_stop_collected', this.pair_id)
      renderer:remove_visible(this.label)
      active = false
    end
  end
end

function main()
  event:register('collision', on_hit)
  event:register('state_changed', on_state_changed)
  active = true
end
