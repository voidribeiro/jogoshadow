function startScript()
  print("Loading Game Menu")

  local gameObject = GameObject.Instantiate("Menu")
  local gui = ComponentGUI.Instantiate()
  
  gui:AddImageButton("StartGame",path .. "resources\\common\\irrlichtlogo.jpg", 121, 129)
  gui:AddImageButton("ExitGame" ,path .. "resources\\common\\irrlichtlogo.jpg", 121, 259)
  
  gui:AddTo(gameObject)

  local script = ComponentScript.Instantiate(path .. "Scripts\\Common\\menu.lua")
  script:AddTo(gameObject)
  
end