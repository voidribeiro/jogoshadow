function startScript()
  
  print("Executando Script de GUI")
  
  local gameObject = GameObject.Instantiate("testeGUI")

  --local component = ComponentInventory.Instantiate()
  
  component:AddImage(path .. "resources\\level1\\textures\\faerie2.bmp")
  
  component:AddTo(gameObject) 

end
