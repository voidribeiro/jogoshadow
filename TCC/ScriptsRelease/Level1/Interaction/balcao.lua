function start()
end

function update()
end

function interact()
  walk()
  local dialog = ComponentDialog.GetFrom("dialogo")
  dialog:Say("Grande de mais para colocar no meu bolso.")
end

function addToInventory()
end

local speachCounter = 0

function inspect()
  walk()
  local dialog = ComponentDialog.GetFrom("dialogo")
  dialog:ClearOptions()

  if (speachCounter < 1) then
    dialog:Say("Outro objeto de cenario.")
  else
    if (speachCounter < 2) then
      dialog:Say("Esse aqui parece que pode ser aberto.")
    else
      if (speachCounter < 3) then
        dialog:Say("Ou talvez empurrado.")
      else
        dialog:Say("Hum... Pelo jeito so mais um objeto inanimado que nao faz nada.")
      end
    end
  end
  speachCounter = speachCounter + 1
end

function walk()
  local selector = ComponentSelector.GetFrom(parentObject)
  local skeleton = ComponentSkeleton.GetFrom("player")
  skeleton:WalkTo(-61.6, -40, 57.5)
end

function interactWith()
end

function destroy()
end