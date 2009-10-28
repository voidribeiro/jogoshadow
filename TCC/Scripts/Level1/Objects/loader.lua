function startScript()
  
  print("Executando Script de GUI")
  
  local gameObject = GameObject.Instantiate()

  local component = ComponentGUI.Instantiate()
  
--  component:AddImage(path .. "resources\\level1\\textures\\faerie2.bmp")
--  component:AddMessageBox("TESTE", "TESTE", true)
  component:AddImage(path .. "resources\\level1\\textures\\portal1.bmp", 300, 300)
  
  component:AddTo(gameObject) 

end
