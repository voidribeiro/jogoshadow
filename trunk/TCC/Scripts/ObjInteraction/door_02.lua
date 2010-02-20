local isInInvetory = 0

function start()
  isInInventory = Game.IsInInventory(parentObject)
end

function interact()
    if (isInInventory == 0) then
      print("adicionou a fada no inventário")
      Game.AddToInventory(parentObject)
      isInInventory = 1
    else
      print("interact da fada no inventário")
    end
end

speachCounter = 0

function inspect()
  if (speachCounter == 0) then
    print("This is another nice door!!!")
    speachCounter = speachCounter + 1
  else
    print("No... this is not a door. It look like one but its an ugly farrie model!!!")
  end
  
end

function interactWith()
  
end

function destroy()
end