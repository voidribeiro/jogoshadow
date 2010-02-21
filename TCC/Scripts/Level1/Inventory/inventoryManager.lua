function start()
	print("Starting inventory manager")
end

local lastButtonPressed = 0;

function update()
  --Binds the object to use its functions
  --local gameObj = GameObject.ReBinder(parentObject)
  local component = ComponentGUI.GetFrom("OBJ_GUI")
  
--  print (component)
  local isInventoryButtonPressed = component:IsButtonPressed("inventoryButton")
  if ((isInventoryButtonPressed > 0) and not (isInventoryButtonPressed == lastButtonPressed)) then
    visible = not Game.IsInventoryVisible();

    print("Apertou")
  	print(component:IsButtonPressed("inventoryButton"))
    Game.DisplayInventory(visible)
  end
  
  lastButtonPressed = isInventoryButtonPressed
  
  Game.DrawInventory()
  --local mouseX,mouseY = Game.GetMousePosition()
  --print(mouseX, mouseY)
end

function destroy()
end