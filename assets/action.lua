require 'std'

Action = Object:new({target=nil, actions={}, passed_time=0, change_time=6})

function Action:update(dt)
  self.passed_time = self.passed_time + dt
  if self.passed_time >= self.change_time then
    self.passed_time = 0
    self:play_action()
  end
end

function Action:play_action()
  local chance = math.random()
  local total = 0
  for i, v in ipairs(self.actions) do
    total = total + v["chance"]
    if total >= chance then
      renderer:play_animation(v["animation"], false)
      if v["sfx"] then
        sfx:play_effect(v["sfx"])
      end
      break
    end
  end
end