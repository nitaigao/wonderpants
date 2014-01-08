function update(dt)
  if not hit then return end
  if failable_timer > 0 then
    failable_timer = failable_timer - dt
    if failable_timer < 0 then
      active = false
      gameplay:pan_to_level_fail()
    end
  end
end

function on_state_changed(state)
  if not active then return end  
  if state == GameState.STATE_LEVEL_WIN or state == GameState.STATE_LEVEL_LOST then
    active = false
  end
end

function on_hit(source, target, material)
  if not active then return end
  if source == this.label then
    hit = true
    failable_timer = 0.5
    event:post('crashable_hit')
  end
end

function main()
  event:register('state_changed', on_state_changed)
  event:register('collision', on_hit)
  active = true
  hit = false
  failable_timer = 0
end