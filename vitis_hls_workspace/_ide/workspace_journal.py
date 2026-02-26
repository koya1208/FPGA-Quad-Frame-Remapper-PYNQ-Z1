# 2026-02-25T18:44:52.835021900
import vitis

client = vitis.create_client()
client.set_workspace(path="vitis_hls_workspace")

comp = client.create_hls_component(name = "hls_component",cfg_file = ["hls_config.cfg"],template = "empty_hls_component")

comp = client.get_component(name="hls_component")
comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")

comp.run(operation="PACKAGE")

vitis.dispose()

vitis.dispose()

