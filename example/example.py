import base64
import json
import sys
import glob
import os
import time
import requests
sys.path.append("/home/a62/GMP/voxelMap/projects/voxelMap/build/src/")
import libvoxelmap
import pcrect
from flask import Flask,request
#Flask类接收一个参数__name__
app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload():
    if request.method == 'POST':
        print(request)
        if request.content_type.startswith('application/json'):
            lasfile  = request.json.get('model_urls')
            utm_xyz = request.json.get('nest_point_utm')
            utm_zone = request.json.get('utm_zone')
            nest_code = request.json.get('nest_code')
            print(type(utm_xyz),type(utm_zone))
            print(type(utm_xyz[0]))
            t1 = time.time()
            print("building voxelmap begin...")
                    
            # m = libvoxelmap.VoxelMap(2, (utm_xyz[0]),utm_xyz[1],utm_xyz[2], nest_code)
            m = libvoxelmap.VoxelMap(2, 258675.2637387041,3774238.6513629877,448.54,49)
            dir_name='/data/xian'
            # lasfile = glob.glob(dir_name+"/*.las")
            for obj in lasfile:     
                            print(obj)
                            f = obj['file']
                            # f = obj
                            # dir_name = os.path.dirname(f)
                            zone = obj['zone']
                            # zone=49
                            t3=time.time()
                            m.addMap(f, zone)
                            t4=time.time()
                            print("add map cost ",t4-t3)
                            
            # for obj in lasfile:
            #                 t3=time.time()
            #                 print(obj)
            #                 # f = obj['file']
            #                 f = obj
            #                 dir_name = os.path.dirname(f)
            #                 # zone = obj['zone']
            #                 zone=49
            #                 m.addMap(f, zone)
            #                 t4=time.time()
            #                 print("add map cost ",t4-t3)

            map_path = os.path.dirname(dir_name)+"/xian"+".bt"
            m.saveMap(map_path)
            print("building voxelmap done")
            
            print("building kml begin...")
            with open(f'{map_path}', 'rb') as btfile:
                            file_content = btfile.read()
                            # 对文件内容进行base64编码
            encoded_content = base64.b64encode(file_content)
            encoded_content_str = encoded_content.decode('utf-8')

            url = 'http://192.168.10.187:8010/v1/orientation/octomap/kml'
            headers = {'Content-Type': 'application/json'}

            data = { "nest_info": [258675.2637387041,3774238.6513629877,448.54,49],'bt_file': encoded_content_str}
            res = requests.post(url , headers=headers, data=json.dumps(data)).json()
            kmlcontent = res["data"]["kml_data"]
            print(kmlcontent)
            print("building kml done")
            # t2 = time.time()
            # print(t2-t1)

            return json.dumps({"state":"OK"})


def getkml():
            # m = libvoxelmap.VoxelMap(2, 258675.2637387041,3774238.6513629877,448.54,49)
            # dir_name='/data/xian'
            # lasfile = glob.glob(dir_name+"/*.las")
            # for obj in lasfile:     
            #                 print(obj)
            #                 # f = obj['file']
            #                 f = obj
            #                 # dir_name = os.path.dirname(f)
            #                 # zone = obj['zone']
            #                 zone=49
            #                 t3=time.time()
            #                 m.addMap(f, zone)
            #                 t4=time.time()
            #                 print("add map cost ",t4-t3)
                            
            map_path="/data/xian.bt"
            # m.saveMap(map_path)
            print("building voxelmap done")
            
            print("building kml begin...")
            with open(f'{map_path}', 'rb') as btfile:
                            file_content = btfile.read()
                            # 对文件内容进行base64编码
            encoded_content = base64.b64encode(file_content)
            encoded_content_str = encoded_content.decode('utf-8')

            url = 'http://192.168.10.187:8010/v1/orientation/octomap/kml'
            headers = {'Content-Type': 'application/json'}

            data = { "nest_info": [258675.2637387041,3774238.6513629877,448.54,49],'bt_file': encoded_content_str}
            res = requests.post(url , headers=headers, data=json.dumps(data)).json()
            kmlcontent = res["data"]["kml_data"]
            print(kmlcontent)
            #decode and save
            # kmldata = base64.b64decode(kmlcontent)
            # kml_path = "/data/xian.kml"
            # with open(kml_path,'wb') as f:
            #                 f.write(kmldata)
            print("building kml done")
            t2 = time.time()
            # print(t2-t1)  

def rect():
    las = '/server-w/3Dreconstruction/杭州视频建模35/B01-35/1dd938bb-8a8e-469c-a99e-5dfd6f7f36a2.laz'
    image_path = ['/server-w/3Dreconstruction/杭州视频建模35/B01-35/images']
    imageFiles = []
    for path in image_path:
        imageFiles.extend(glob.glob(path+"/*.*"))
    camjson = '/server-w/3Dreconstruction/杭州视频建模35/B01-35/1dd938bb-8a8e-469c-a99e-5dfd6f7f36a2.geojson'
    save_dsm = '/server-w/3Dreconstruction/杭州视频建模35/B01-35/manual.tif'
    # pc_out = '/home/a62/GMP/open3d/jiagnshanshimen/10/10-georeferenced_model_rect.las'
    # dsm_out = '/server-w/3Dreconstruction/杭州视频建模35/B01-35/'+ time.strftime("%Y-%m-%d-%H_%M_%S",time.localtime(time.time()))+'.tif'
    t1 = time.time()
    # tif = '/server-w/3Dreconstruction/万田/02/5ad1442c-44a7-4d87-b6be-2d7537c257b1.tif'
    # read_tif(tif)
    # rectply='/server-w/3Dreconstruction/杭州视频建模35/B01-35/manual_rect.ply'
    # generatedsmUTM(rectply,dsm_out)
    pcrect.rectify(las,imageFiles,camjson,save_dsm,32651)
    # file_list = glob.glob('/server-w/3Dreconstruction/无锡视频建模35'+'/**/*.tif')
  
    # mergeTif(file_list, dsm_out)
    t2= time.time()
    print(t2-t1)
    


if __name__ == '__main__':
    #  getkml()
    rect()
    # app.run(host='0.0.0.0',port=35353)
