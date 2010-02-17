function start()
	print("Starting inventory manager")
end

visible = false

function update()
  --Binds the object to use its functions
  --local gameObj = GameObject.ReBinder(parentObject)
  local component = ComponentGUI.GetFrom("OBJ_GUI")
  
--  print (component)
  if component:IsButtonPressed("inventoryButton") > 0 then
    visible = not visible

    print("Apertou")
  	print(component:IsButtonPressed("inventoryButton"))

  end
  Game.DisplayInventory(visible)
  Game.DrawInventory()
  --local mouseX,mouseY = Game.GetMousePosition()
  --print(mouseX, mouseY)
end

function destroy()
end