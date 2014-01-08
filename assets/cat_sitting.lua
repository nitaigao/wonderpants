require 'action'
require 'maths'

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

function face_player()
  local l = component:get_all("launchable")
  for i, v in ipairs(l) do
    local targetable_spatial = component:get('spatial')
    local launchable_spatial = component:get('spatial', v.label)
  
    local x_difference = targetable_spatial.x - launchable_spatial.x
  
    if facing_direction < 0 and x_difference < 0 then
      renderer:flip_x(this.label)      
      facing_direction = 1
    end

    if facing_direction > 0 and x_difference > 0 then
      renderer:flip_x(this.label)      
      facing_direction = -1
    end
  end  
end

function on_cat_anticipated()
  renderer:play_animation("cat_anticipation_paws", true)
end

function on_launchable_close_to_targettable()
  if not anticipating and anticipation_timeout <= 0 then
    anticipating = true
    renderer:play_animation("cat_anticipation", false, false, on_cat_anticipated)
  end
end

function on_launchable_not_close_to_targettable()
  if anticipating then
    anticipating = false
    renderer:play_animation("cat_deanticipation", false, false)
    anticipation_timeout = 3
  end
end

function calculate_anticipation()
  local spatial = component:get('spatial')
  local position = Vector:new({x=spatial.x, y=spatial.y})
  for i, v in ipairs(launchable_spatials) do
    local launchable_position = Vector:new({x=v.x, y=v.y})
    local distance = position:distance(launchable_position)
    
    if distance < 125 then
      on_launchable_close_to_targettable()      
    end
    
    if distance > 200 then
      on_launchable_not_close_to_targettable()
    end
  end
end

function update(dt)
  if not active then return end   
  if not anticipating then
    idle_action:update(dt)    
  end
  
  if anticipation_timeout > 0 then
    anticipation_timeout = anticipation_timeout - dt
  end
  
  calculate_anticipation()
  face_player()
end

function on_state_changed(state)
  if not active then return end
  
  if state == GameState.STATE_LEVEL_START then
    local launchables = component:get_all('launchable')
    for i, v in ipairs(launchables) do
      local spatial = component:get("spatial", v.label)
      table.insert(launchable_spatials, spatial)
    end
  end
  
  if state == GameState.STATE_LEVEL_LOST then
    local l = component:get_all("launchable")
    for i, v in ipairs(l) do
      local targetable_spatial = component:get('spatial', v.label)
      local launchable_spatial = component:get('spatial')
      if launchable_spatial.y > targetable_spatial.y + 20 then
        renderer:play_animation("cat_missed_below", false, false)
      else
        renderer:play_animation("cat_missed", true)
      end
      sfx:play_effect('cat_sad')
    end
  end
  
  if state == GameState.STATE_LEVEL_WIN or 
     state == GameState.STATE_LEVEL_LOST then
    active = false
  end
end

function main()
  event:register('state_changed', on_state_changed)
  
  idle_action = Action:new({target=this, actions=ACTIONS, change_time=3})
  active = true
  anticipating = false
  facing_direction = -1 -- left
  anticipation_timeout = 0
  launchable_spatials = {}
end