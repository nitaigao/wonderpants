require 'maths'
require 'table'

BOOST = 15.0
active = true

BOUNCABLE = {
  "cat",
  "launchable"
}

function on_state_changed(state)
  if state == GameState.STATE_LEVEL_WIN or state == GameState.STATE_LEVEL_LOST then
    active = false
  end
end

function on_hit(source, target, material)
  if not active then return end
  if source == this.label and table.contains_value(BOUNCABLE, material) then
    local bounce_spatial = component:get('spatial')
    local bounce_position = Vector:new({x=bounce_spatial.x, y=bounce_spatial.y})
    
    local target_spatial = component:get('spatial', target)
    local target_position = Vector:new({x=target_spatial.x, y=target_spatial.y})
    
    -- when we bounce we want to nudge towards the center of the bouncey a bit, this prevents us from getting stuck    

    -- calculate teh distance between us and the bouncey
    local towards_bounce = bounce_position - target_position
     -- translate up a bit so that we dont nudge directly to the center of the bouncey
    local bounce_up = Vector:new({x=0, y=10}):rotate(-bounce_spatial.rotation)
    -- calculate the new slightly nudged position
    local nudged_position = target_position + (towards_bounce * 0.2) + bounce_up
    -- move to that position
    transform:set_translation(nudged_position.x, nudged_position.y, target)
  
    forward_boost_direction = Vector:new({x=0, y=1}):rotate(-bounce_spatial.rotation)
    physics:stop_motion(target)
    physics:apply_impulse(forward_boost_direction, BOOST, target)
    renderer:play_animation('boing_bounce', false, false)
    sfx:play_effect('darrell_collide')
    event:post('bouncable_hit', target)
  end
end

function main()
  event:register('state_changed', on_state_changed)
  event:register('collision', on_hit)
  active = true
end