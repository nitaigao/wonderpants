table = table or {}

function table.contains_key(t, key)
  for k, v in pairs(t) do
    if k == key then
      return true
    end
  end
  return false
end

function table.contains_value(table, element)
  for _, value in pairs(table) do
    if value == element then
      return true
    end
  end
  return false
end