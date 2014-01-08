require 'maths'
require 'table'

MISSABLE = {
  "teleport",
  "coin"
}

function update(dt)
  if not active then return end
  physics:apply_impulse(direction, 0.025, this.label)
  local arrow_spatial = component:get('spatial')
  if not renderer:on_screen(arrow_spatial.x, arrow_spatial.y) then
    entity:destroy()
  end
end

function on_state_changed(state)  
  if state == GameState.STATE_LEVEL_WIN or 
     state == GameState.STATE_LEVEL_LOST then
    active = false
    entity:destroy()
  end
end

function air_fail()
  active = false
  entity:destroy()
end

function on_inca_stop_collected(pair_id)
  if not active then return end
  if this.pair_id == pair_id then
    local spatial = component:get('spatial')
    particles:emit('arrow_fire_smoke', this.label)
    active = false
    entity:destroy()    
  end
end


function on_hit(source, target, material)
  if not active then return end
  if source == this.label and not table.contains_value(MISSABLE, material) then
    event:post('arrow_hit', target)
    active = false
    entity:destroy()
  end
end

function main()
  event:register('state_changed', on_state_changed)
  event:register('collision', on_hit)
  event:register('air_fail', air_fail)
  event:register('inca_stop_collected', on_inca_stop_collected)    
  
  local spatial = component:get('spatial')
  local up = Vector:up()
  direction = up:rotate(90 - spatial.rotation):normalize_slow()
  active = true
  
end