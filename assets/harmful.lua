function on_state_changed(state)
  if state == GameState.STATE_LEVEL_WIN and active or state == GameState.STATE_LEVEL_LOST and active then
    active = false
  end
end

function on_hit(source, target, material)
  if active and source == this.label then
    active = false
    event:post('air_fail')
    sfx:play_effect('level_lose')
    sfx:play_effect('darrell_fail')
    sfx:play_effect('cat_sad')
  end
end

function main()
  event:register('state_changed', on_state_changed)
  event:register('collision', on_hit)
  active = true
end