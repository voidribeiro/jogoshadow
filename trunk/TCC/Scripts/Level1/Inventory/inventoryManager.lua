function start()
	print("Starting inventory manager")
end

function update()
  --Binds the object to use its functions
  --local gameObj = GameObject.ReBinder(parentObject)
  local component = ComponentGUI.GetFrom("OBJ_GUI")
--  print (component)
  if component:IsButtonPressed("inventoryButton") > 0 then
	print("Apertou")
	print(component:IsButtonPressed("inventoryButton"))
  end
end

function destroy()
end