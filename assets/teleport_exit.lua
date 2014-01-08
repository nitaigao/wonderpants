function update(dt)
  if not active then return end
  
  if animation_time > -1 then
    animation_time = animation_time - dt
    if animation_time < 0 then
      renderer:set_visible(false, this.label)
      animation_time = -1
    end
  end
end

function on_entrance_hit(pair_id, subject)
  if not active then return end
  if pair_id == this.pair_id then
    local spatial = component:get('spatial')    
    transform:set_translation(spatial.x, spatial.y, subject)
    animation_time = 0.3
    renderer:set_visible(true, this.label)
  end
end

function main()
  event:register('teleport_entrance_hit', on_entrance_hit)
  active = true
  animation_time = -1
end