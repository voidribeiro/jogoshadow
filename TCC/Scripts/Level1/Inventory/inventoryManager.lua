function start()
	print("Starting inventory manager")
end

function update()
  --Binds the object to use its functions
  local gameObj = GameObject.ReBind(parentObject)
--  local component = gameObj:GetComponentOfType(6)
--  if component:IsButtonPressed("inventoryButton")
--	print("Apertou")
--  end
end

function destroy()
end