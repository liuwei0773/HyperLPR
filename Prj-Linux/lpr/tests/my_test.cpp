#include "../include/Pipeline.h"

int main(){
   pr::PipelinePR prc("model/cascade.xml",
                       "model/HorizonalFinemapping.prototxt","model/HorizonalFinemapping.caffemodel",
                       "model/Segmentation.prototxt","model/Segmentation.caffemodel",
                       "model/CharacterRecognization.prototxt","model/CharacterRecognization.caffemodel",
                       "model/SegmenationFree-Inception.prototxt","model/SegmenationFree-Inception.caffemodel"
    );
  //定义模型文件

    cv::Mat image = cv::imread("res/test1.jpg");
    std::vector<pr::PlateInfo> res = prc.RunPiplineAsImage(image,pr::SEGMENTATION_FREE_METHOD);
  //使用端到端模型模型进行识别 识别结果将会保存在res里面
 
    for(auto st:res) {
        if(st.confidence>0.75) {
            std::cout << st.getPlateName() << " " << st.confidence << std::endl;
          //输出识别结果 、识别置信度
            cv::Rect region = st.getPlateRect();
          //获取车牌位置
 cv::rectangle(image,cv::Point(region.x,region.y),cv::Point(region.x+region.width,region.y+region.height),cv::Scalar(255,255,0),2);
          //画出车牌位置
          
        }
    }

    cv::imshow("image",image);
    cv::waitKey(0);
    return 0 ;
}