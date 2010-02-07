function start()
	print("Starting input")
end

function update()
  
  local mouseButton = Game.GetMouseClick()
  if(mouseButton == 1) then
  
    local mouseX,mouseY = Game.GetMousePosition()
    print(mouseX, mouseY)
  
  end
  
end

function destroy()
end