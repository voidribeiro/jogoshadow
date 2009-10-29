function startScript()
  
  print("Executando Script de GUI")
  
  local gameObject = GameObject.Instantiate()

  local component = ComponentGUI.Instantiate()
  
--  component:AddImage(path .. "resources\\level1\\textures\\faerie2.bmp")
  --component:AddMessageBox("TESTE", "TESTE", true)
  
  component:AddTo(gameObject) 

end
