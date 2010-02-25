function start()
end

function update()
end

function interact()
  walk()
  local dialog = ComponentDialog.GetFrom("dialogo")
  dialog:Say("Melhor deixar a estante onde esta.")
end

function addToInventory()
end

local speachCounter = 0

function inspect()
  walk()
  local dialog = ComponentDialog.GetFrom("dialogo")
  dialog:ClearOptions()

  if (speachCounter < 1) then
    dialog:Say("Uma instante cheia de livros.")
  else
    if (speachCounter < 2) then
      dialog:Say("Tem um livro estranho chamado El Matador.")
    else
      if (speachCounter < 3) then
        dialog:Say("E outro chamado o Gorila de botas. Estranho, achei que so ouvessem gatos com botas.")
      else
        dialog:Say("Nao vou ler nada agora.")
      end
    end
  end
  speachCounter = speachCounter + 1
end

function walk()
  local selector = ComponentSelector.GetFrom(parentObject)
  local skeleton = ComponentSkeleton.GetFrom("player")
  skeleton:WalkTo(-12, -40, 63.7)
end

function interactWith()
end

function destroy()
end