require 'maths'

LAUNCH_TIME = 2
FACING = 0

function fire_arrow()
  local spatial = component:get('spatial')
  local position = Vector:new({x=spatial.x,y=spatial.y})
  
  rotation = FACING == 0 and spatial.rotation or 180 + spatial.rotation
  
  sfx:play_effect('arrow_blow')
    
  local mouth_offset = -10
  if FACING == 1 then
    mouth_offset = 10
  end
    
  local rotated_mouth = Vector:new({x=0,y=mouth_offset}):rotate(-rotation)
  local mouth_position = position + rotated_mouth
  
  local arrow_label = entity:spawn('inca_arrow', mouth_position.x, mouth_position.y, rotation)
  local arrow = component:get('inca_arrow', arrow_label)
  arrow.pair_id = this.pair_id
  particles:emit('arrow_fire_smoke', this.label, rotated_mouth.x, rotated_mouth.y)
end

function update(dt)
  if not active then return end
  
  timer = timer + dt
  
  if timer >= LAUNCH_TIME then
    timer = 0
    fire_arrow()
  end
end

function on_state_changed(state)
  if state == GameState.STATE_LEVEL_START then
    active = true
    timer = 0
  end
  
  if state == GameState.STATE_LEVEL_WIN or state == GameState.STATE_LEVEL_LOST then
    active = false
  end
end

function on_stop_collected(pair_id)
  if not active then return end
  if pair_id == this.pair_id then
    active = false    
    renderer:play_animation('inca_disabled', false, false)
  end
end

function main()
  event:register('state_changed', on_state_changed)
  event:register('inca_stop_collected', on_stop_collected)
  active = false
  timer = 0
end
