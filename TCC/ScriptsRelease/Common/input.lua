function start()
	print("Starting input")
end

local oldMouseLeftButton = 0
local oldMouseRightButton = 0

function update()
  
  local mouseLeftButton = Game.GetMouseLeft()
  local mouseRightButton = Game.GetMouseRight()
  if (((mouseLeftButton == 1) and not (oldMouseLeftButton == mouseLeftButton))
  or ((mouseRightButton == 1) and not (oldMouseRightButton == mouseRightButton))) then
  
    --local mouseX,mouseY = Game.GetMousePosition()
    --print(mouseX, mouseY)
    local interact = Game.PickNearestInteract()
    if (interact) then
      if (mouseLeftButton == 1) then
        interact:Inspect()
      else
        local selItem = Game.GetSelectedItem()
        if (selItem == "") then
          interact:Interact()
        else
          interact:InteractWith(selItem)
        end
      end
    end
  end
  
  oldMouseLeftButton = mouseLeftButton;
  oldMouseRightButton = mouseRightButton;
  
end

function destroy()
end