function on_state_changed(state)
  if state == GameState.STATE_LEVEL_WIN or 
     state == GameState.STATE_LEVEL_LOST and active then
    active = false
  end
end

function update(dt)
  if animation_time > -1 then
    animation_time = animation_time - dt
    if animation_time < 0 then
      renderer:set_visible(true, this.label)
      animation_time = -1
    end
  end
end

function on_hit(source, target, material)
  if active and source == this.label then
    if material == "launchable" then
      event:post('teleport_entrance_hit', this.pair_id, target)
      sfx:play_effect("teleport")
      animation_time = 0.4
      renderer:set_visible(false, this.label)
    end
  end
end

function main()
  event:register('state_changed', on_state_changed)
  event:register('collision', on_hit)
  active = true
  animation_time = -1
end