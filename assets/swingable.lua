require 'maths'

GRAB_RADIUS = 100

function on_state_changed(state)
  if state == GameState.STATE_LEVEL_WIN or state == GameState.STATE_LEVEL_LOST then
    active = false
  end
  if state == GameState.STATE_LEVEL_START then
    local point_spatial = component:get('spatial')
    gameplay:spawn_swing_circle(GRAB_RADIUS, point_spatial.x, point_spatial.y, this.label)
  end
end

function on_swing_started(swingee_label, swing_point_label)
  if not active then return end
  if this.label == swing_point_label then
    swinger_label = swingee_label
    swinging = true  
    current_animation = animation_states.ATTACHED
    renderer:play_animation('swing_attached', true)
    transform:look_at(swinger_label, -95)
  end
end

function on_swing_stopped()
  if not active then return end
  swinging = false
  current_animation = animation_states.DETACHED
  renderer:play_animation('swing_detached', true)
  transform:stop_look_at(swinger_label)
end

function on_swing_close(label)
  if not active then return end
  if not swinging and label == this.label then
    current_animation = animation_states.CLOSE
  end
end

function on_swing_far(label)
  if not active then return end
  if not swinging and label == this.label then
    current_animation = animation_states.DETACHED
   --  renderer:play_animation('swing_detached', true)
  end
end

function main()
  event:register('swing_started', on_swing_started)
  event:register('swing_stopped', on_swing_stopped)
  event:register('swing_point_close', on_swing_close)
  event:register('swing_point_far', on_swing_far)
  event:register('state_changed', on_state_changed)
  swinging = false  
  active = true
  animation_states = {
    DETACHED = 0,
    ATTACHED = 1,
    CLOSE = 2
  }
  
  current_animation = animation_states.DETACHED
end