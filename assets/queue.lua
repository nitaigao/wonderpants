require 'std'

Queue = Object:new({size=5})

function Queue:clear()
  for i = 1, self.size do
    self:add(0)
  end  
end

function Queue:empty()
  self = Queue:new({self = self.size})
end

function Queue:add(value)
  table.insert(self, 1, value)
  
  if table.getn(self) > self.size then
    table.remove(self)
  end
end

function Queue:average()
  local total = 0
  for i in ipairs(self) do
    total = total + self[i]
  end
  return total / table.getn(self)
end

function Queue:max()
  local max = 0
  for i in ipairs(self) do
     if self[i] > max then max = self[i] end
  end
  return max
end

function Queue:min()
  local min = 0
  for i in ipairs(self) do
     if self[i] < min then min = self[i] end
  end
  return min
end