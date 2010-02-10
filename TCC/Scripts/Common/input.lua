function start()
	print("Starting input")
end

function update()
  
  local mouseButton = Game.GetMouseClick()
  if(mouseButton == 1) then
  
    --local mouseX,mouseY = Game.GetMousePosition()
    --print(mouseX, mouseY)
    local interact = Game.PickNearestInteract()
    if (interact) then
      interact:Inspect()
    end
  end
  
end

function destroy()
end