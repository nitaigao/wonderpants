require 'table'
require 'maths'

LaunchState = {
  INVALID = 0,
  PRE_LAUNCH = 1,
  PRE_LAUNCH_DEAD_ZONE = 1.5,
  CHARGE = 2,
  FIRE = 3,
  POST_LAUNCH = 4,
  POST_CHARGE = 5,
  PRE_FINISH = 6,
  LAUNCH_FINISHED = 7
}
 
function update(dt)
  if not active then return end
    
  if launchState == LaunchState.PRE_LAUNCH_DEAD_ZONE then
    launch_timer = launch_timer + dt
    if launch_timer > LAUNCH_TIME_THRESHOLD then
      event:post('launchable_charging')
      launchState = LaunchState.CHARGE
    end
  end

  if launchState == LaunchState.CHARGE and strength < MAX_STRENGTH or 
     launchState == LaunchState.POST_CHARGE and strength < MAX_STRENGTH then
    strength = strength + STRENGTH_INC * dt * 60
    local boost_percent = math.min(strength / MAX_STRENGTH, 1.0)
    gameplay:set_boost(boost_percent)
    if strength >= MAX_STRENGTH then
      event:post('launchable_max_charge')
    end
  end
end

function on_input_started()
  if not active then return end
  if launchState == LaunchState.PRE_LAUNCH then
    launchState = LaunchState.PRE_LAUNCH_DEAD_ZONE
    launch_timer = 0
  end
end

function on_input_ended()
  if not active then return end
  if launchState == LaunchState.PRE_LAUNCH_DEAD_ZONE and launch_timer < LAUNCH_TIME_THRESHOLD then
    launchState = LaunchState.PRE_LAUNCH
  end

  if launchState == LaunchState.CHARGE then
    event:post('launchable_launched', strength, MAX_STRENGTH)
    launchState = LaunchState.FIRE

    physics:set_dynamic(this.label)
    physics:apply_impulse(forward_boost_direction, strength, this.label)
  end
  
  if launch_timer < LAUNCH_TIME_THRESHOLD then
    event:post('launchable_launch_cancelled')
  end
end

function on_state_changed(state)
  if not active then return end  
  if state == GameState.STATE_LEVEL_WIN or state == GameState.STATE_LEVEL_LOST then
    active = false
  end
end

function on_hit(source, target, material)
  if active and source == this.label then
    event:post("launchable_collision", source, target, material)
    if material == "" or material == nil then
      collisions = collisions + 1
      local bonus = 50
      gameplay:remove_bonus(bonus)
    end
  end
end

function on_crashable_hit()
  if not active then return end  
  active = false
  event:post('launchable_crashed')
  physics:stop_motion(this.label)
  physics:make_sensor(this.label)
  physics:set_active(false, this.label)
end

function on_input_disabled()
  event:unregister('input_started', on_input_started);
  event:unregister('input_ended', on_input_ended);
end

function on_input_enabled()
  event:register('input_started', on_input_started);
  event:register('input_ended', on_input_ended);
end

function main()
  active = true
  strength = 0
  launch_timer = 0
  collisions = 0
  launchState = LaunchState.PRE_LAUNCH
  
  MAX_STRENGTH = 65.0
  STRENGTH_INC = 0.8
  LAUNCH_TIME_THRESHOLD = 0.1
  
  forward_boost_direction = Vector:new({x=0.18, y=0.3})

  event:register('input_started', on_input_started);
  event:register('input_ended', on_input_ended);
  event:register('state_changed', on_state_changed)
  event:register('crashable_hit', on_crashable_hit)
  event:register('collision', on_hit)
  event:register('input_disabled', on_input_disabled)
  event:register('input_enabled', on_input_enabled)
  
  physics:set_active(true, this.label)
end