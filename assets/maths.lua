require 'std'

Vector = Object:new({x = 0, y = 0})

function Vector:up()
  return Vector:new({x=0,y=1})
end

function Vector:right()
  return Vector:new({x=1,y=0})
end

function Vector:scale(amount)
  return Vector:new({ x = self.x * amount, 
                      y = self.y * amount })
end

function Vector:identity()
  return Vector:new({x = 0, y = 0})
end

function Vector:dot(a)
  return (self.x * a.x) + (self.y * a.y)
end

function Vector:angle(a)
  return math.acos(self:dot(a))
end

function Vector:distance(a)
  return (a - self):length()
end

function Vector:normalize_fast()
  local ax = math.abs(self.x)
  local ay = math.abs(self.y)
  
  local ratio = 1 / math.max(ax, ay)
  ratio = ratio * (1.29289 - (ax + ay) * ratio * 0.29289)
  
  return Vector:new({x=self.x*ratio, y=self.y*ratio})
end

function Vector:normalize_slow()
  local length = self:length()
  return Vector:new({x=self.x / length, y=self.y / length})
end

function Vector:length() 
  return math.sqrt(self.x*self.x + self.y*self.y)
end

function Vector:cross(a)
  return self.x * a.y - a.x * self.y;
end

function Vector:inverse()
  return -self
end

function Vector.__unm(a)
  return Vector:new({ x = -a.x,
                      y = -a.y })  
end

function Vector.__add(a, b)
  return Vector:new({ x = a.x + b.x,
                      y = a.y + b.y })
end

function Vector.__sub(a, b)
  return Vector:new({ x = a.x - b.x,
                      y = a.y - b.y })
end

function Vector.__mul(a, b)
  return Vector:new({ x = a.x * b.x,
                      y = a.y * b.y })
end

function Vector.__mul(a, scalar)
  return Vector:new({ x = a.x * scalar,
                      y = a.y * scalar })  
end

function Vector:string()
  return '{x:' .. self.x .. ' y:' .. self.y .. '}'
end

function Vector:rotate(degrees)
  local radians = radians(degrees)
  return Vector:new({ x = (self.x * math.cos(radians)) - (self.y * math.sin(radians)),
                      y = (self.x * math.sin(radians)) + (self.y * math.cos(radians)) })
end

function degrees(radians)
  return (radians * 180) / math.pi
end

function radians(degrees)
  return (degrees * math.pi) / 180
end