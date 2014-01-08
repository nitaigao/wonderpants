function reset_orientation()
  local spatial = component:get('spatial')
  transform:rotate(radians(spatial.rotation))
end