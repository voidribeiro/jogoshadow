function start()
	print("Starting inventory manager")
end

show = false

function update()
  --Binds the object to use its functions
  --local gameObj = GameObject.ReBinder(parentObject)
  local component = ComponentGUI.GetFrom("OBJ_GUI")
--  print (component)
  if component:IsButtonPressed("inventoryButton") > 0 then
    
    Game.DisplayInventory(true)

    print("Apertou")
  	print(component:IsButtonPressed("inventoryButton"))

  end
  --local mouseX,mouseY = Game.GetMousePosition()
  --print(mouseX, mouseY)
end

function destroy()
end