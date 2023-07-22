# OPENCV-ASCII-ART-and-Video
This project is an ASCII art generator that converts an input image into its ASCII art representation. The program reads a grayscale image from the specified path and processes it to generate the corresponding ASCII art. The resulting ASCII art can be displayed on the screen and optionally saved as an image file. In future and a video

#Project Usage and Parameters:

Input Image Path (path): The path to the grayscale image that will be used to generate ASCII art. The image should be in a format compatible with OpenCV's imread function.

Safe Image or Not (SafeImgOrNot): A boolean flag that determines whether to save the generated ASCII art as an image file. If set to true, the ASCII art will be saved. If set to false, the ASCII art will be displayed on the screen but not saved.

Path to Safe ASCII Image (PathToSafeAsciiImg): The path and filename for saving the generated ASCII art as an image. This parameter is applicable only if SafeImgOrNot is set to true.

Character Size (char_size): The size of the ASCII characters used in the art. A larger char_size value may result in lower quality ASCII art, while a smaller value may yield higher quality art. Adjust this parameter based on personal preference and output size.
