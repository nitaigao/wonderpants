require 'action'

ACTIONS = {
  {
    animation = "cat_idle", 
    chance = 0.1
  },
  {
    animation = "cat_blink", 
    chance = 0.4  
  },
  {
    animation = "cat_meow", 
    chance = 0.5,
    sfx = "cat_meow"
  }
}

function update(dt)
  if not active then return end   
  idle_action:update(dt)
end

function on_state_changed(state)
  if not active then return end
  
  if state == GameState.STATE_LEVEL_LOST then   
    renderer:play_animation('cat_missed', true) 
    sfx:play_effect('cat_sad')
  end
  
  if state == GameState.STATE_LEVEL_WIN or 
     state == GameState.STATE_LEVEL_LOST and active then
    active = false
  end
end

function main()
  active = true
  event:register('state_changed', on_state_changed)
  idle_action = Action:new({target=this, actions=ACTIONS, change_time=3})
end