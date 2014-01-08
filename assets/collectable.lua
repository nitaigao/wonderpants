require 'maths'
require 'color'

function on_state_changed(state)
  if not active then return end
  if state == GameState.STATE_LEVEL_WIN or state == GameState.STATE_LEVEL_LOST and active then
    active = false
  end
end

function on_coin_collected()
  coins_collected = coins_collected + 1
end

function on_hit(source, target, material)
  if not active then return end
  if source == this.label then
    local l = component:get_all("launchable")
    local spatial = component:get('spatial')
      
    for i, v in ipairs(l) do    
      if target == v.label then
        this.collected = true
        active = false
        particles:emit('collect_star', this.label)
        sfx:play_effect('collect' .. coins_collected)
        
        local spawn_position = Vector:new({x=spatial.x, y=spatial.y})
        local bonus = 1000
        gameplay:spawn_floaty_score(spawn_position, COLOR.RED, bonus)
        gameplay:add_bonus(bonus)
        event:post("coin_collected", this.label)
        renderer:remove_animable(this.label)
      end    
    end  
  end
end

function main()
  event:register('state_changed', on_state_changed)
  event:register('coin_collected', on_coin_collected)
  event:register('collision', on_hit)
  coins_collected = 0
  active = true
end