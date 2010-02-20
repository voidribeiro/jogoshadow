function start()
end


function update()
  local component = ComponentGUI.GetFrom("Menu")
  
  if component:IsButtonPressed("StartGame") > 0 then
    Game.LoadLevel("Level1")
  end  

  if component:IsButtonPressed("ExitGame") > 0 then
    Game.End();
  end 

end

function destroy()
end