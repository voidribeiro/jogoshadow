function start()
	print("Starting inventory manager")
end

local lastButtonPressed = 0;

function update()
  local component = ComponentGUI.GetFrom("INV_GUI")
  
  local isInventoryButtonPressed = component:IsButtonPressed("inventoryButton")
  if ((isInventoryButtonPressed > 0) and not (isInventoryButtonPressed == lastButtonPressed)) then
    local visible = false
    if (Game.IsInventoryVisible() == 0) then
      visible = true
    end
    
  	print("Inventario visivel: ",visible)
    Game.DisplayInventory(visible)
  end
  
  lastButtonPressed = isInventoryButtonPressed
  
  Game.DrawInventory()
end

function destroy()
end