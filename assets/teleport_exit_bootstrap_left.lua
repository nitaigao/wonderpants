function on_state_changed(state)
  if state == GameState.STATE_LEVEL_START then
    local spatial = component:get('spatial')
    local label = entity:spawn('teleport_exit_red_left', spatial.x, spatial.y - 8, spatial.rotation)
    local exit = component:get('teleport_exit', label)
    exit.pair_id = this.pair_id
  end
end

function on_teleport_entrance_hit(source, target)
  if not active then return end
  if this.pair_id == source then
    renderer:play_animation('teleport_exit_open_left')
  end
end

function main()
  event:register('state_changed', on_state_changed)
  event:register('teleport_entrance_hit', on_teleport_entrance_hit)
  active = true
end