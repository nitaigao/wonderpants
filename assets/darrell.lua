require 'action'
require 'maths'
require 'reset_orientation'

ACTIONS = {
  {
    animation = "idle", 
    chance = 0.3
  },
  {
    animation = "character_blink", 
    chance = 0.6
  },
  {
    animation = "pants", 
    chance = 0.1
  }
}

function stop_jump_sound(strength, max_strength)
  sfx:stop_effect("darrell_launch_low")  
  sfx:stop_effect("darrell_launch_med")  
  sfx:stop_effect("darrell_launch_high") 
end

function play_jump_sound(strength, max_strength)
  local strength_percentage = (strength / max_strength) * 100
  local jump_sound = "darrell_launch_low"
  if strength_percentage > 30 then 
    jump_sound = "darrell_launch_med"
  end
  if strength_percentage > 70 then 
    jump_sound = "darrell_launch_high"
  end
  if strength_percentage >= 100 then
    jump_sound = "darrell_full_power"
  end
  sfx:play_effect(jump_sound)
end

function flip_for_travel_directon()
  if not direction then
    renderer:flip_x(this.label)
  end
end

function jitter() 
  local angle = math.random()
  local x = (original_position.x * math.cos(angle)) - (original_position.y * math.sin(angle))  
  local scale_factor = 60
  x = x / scale_factor
  transform:set_translation(original_position.x + x, original_position.y)  
end

function update(dt)
  if not active then return end
  
  if allow_idle then
    idle_action:update(dt)
  end
  
  if max_charge then
    jitter()
  end
  
  if air_smoke then
    hangtime = hangtime + dt
    if hangtime > IN_AIR_SMOKE_THRESHOLD then
      particles:stop('flight_smoke', this.label)
      air_smoke = false
    end
  end
end

function on_jump_max()
  sfx:play_effect('charge_full')
  sfx:play_effect('darrell_full_power')
  max_charge = true
end

function on_charging()
  if not active then return end
  particles:emit('side_smoke_l', this.label, 0, -32)
  particles:emit('side_smoke_r', this.label, 0, -32)
  renderer:play_animation('prejump', false, false, on_jump_max)
  sfx:play_effect('charge_jump')
  allow_idle = false
end

function on_launched(strength, max_strength)
  if not active then return end
  allow_idle = false
  renderer:play_animation('launched', true)
  sfx:stop_effect('charge_jump')
  	  
  particles:stop('side_smoke_l', this.label)
  particles:stop('side_smoke_r', this.label)
  particles:emit('flight_smoke', this.label)
  
  sfx:play_effect('jump')
  play_jump_sound(strength, max_strength)
  max_charge = false
  air_smoke = true
  launchable_launched = true
end

function on_air_fail()
  if not active then return end
  renderer:play_animation('missed', true)
  sfx:play_effect('darrell_fail')
  local spatial = component:get('spatial')
  flip_for_travel_directon()
  physics:set_dynamic(this.label)
  physics:set_linear_dampening(0, this.label)
  physics:make_sensor(this.label)
  physics:disable_collisions(this.label)
end

function on_arrow_hit(target)
  if not active then return end
  if this.label == target then 
    event:post('air_fail')
  end
end

function on_hit_target() 
  if not active then return end
  renderer:play_animation('win', true)
  sfx:play_effect('darrell_collect')
  if air_smoke then
	  particles:stop('flight_smoke', this.label)
	end
end

function on_state_changed(state)
  if not active then return end  
  
  if state == GameState.STATE_LEVEL_WIN or state == GameState.STATE_LEVEL_LOST then
    active = false
  end
  
  if state == GameState.STATE_LEVEL_START then
    local spatial = component:get('spatial')
    original_position = Vector:new({x=spatial.x, y=spatial.y})    
  end
end

function on_crashable_hit()
  if not active then return end

  local screen_size = renderer:screen_size()
 
  local screen_size = renderer:screen_size()
  local spatial = component:get('spatial')
  
  if spatial.x > 435 then
    transform:set_translation(435, spatial.y)
  end
  
  if spatial.x < 45 then
    transform:set_translation(45, spatial.y)
  end
  
  stop_jump_sound()
  
  renderer:play_animation('fallen', true)
  sfx:play_effect('crash_land')
  flip_for_travel_directon()
  if air_smoke then
	  particles:stop('flight_smoke', this.label)
	end
	renderer:shake_camera()
	reset_orientation()
end

function reset_orientation()
  local spatial = component:get('spatial')
  transform:rotate(radians(spatial.rotation))
end

function on_failable_hit()
  renderer:play_animation('missed', true)
  sfx:play_effect('darrell_fail')
  physics:disable_collisions(this.label)
end

function main()
  event:register('state_changed', on_state_changed)
  event:register('launchable_charging', on_charging)
  event:register('launchable_launched', on_launched)
  event:register('air_fail', on_air_fail)
  event:register('targetable_collected', on_hit_target)
  event:register('crashable_hit', on_crashable_hit)
  event:register('arrow_hit',on_arrow_hit)
  event:register('failable_hit', on_failable_hit)

  active = true
  allow_idle = true
  max_charge = false
  air_smoke = false
  hangtime = 0
  idle_action = Action:new({target=this, actions=ACTIONS, change_time=4})
  last_x = 0
  direction = true
  launched = false
  
  IN_AIR_SMOKE_THRESHOLD = 1.0
end