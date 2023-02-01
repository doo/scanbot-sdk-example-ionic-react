
import json
from xml.dom import minidom

package_json = {}
plugin_xml = {}

with open('package.json', 'r') as file:
    package_json = json.load(file)

package_version = package_json["version"]

with open('plugin.xml', 'r') as file:
    plugin_xml = minidom.parse(file)

plugin_version = plugin_xml.getElementsByTagName("plugin")[0].getAttribute("version")

if package_version != plugin_version:
    raise Exception("package.json version number does not equal plugin.xml version number")
