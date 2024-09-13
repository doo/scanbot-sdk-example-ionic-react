import { Camera, CameraResultType, CameraSource } from "@capacitor/camera";

export const PickImage = async () => {
    const image = await Camera.getPhoto({
        resultType: CameraResultType.Uri,
        source: CameraSource.Photos,
    });
    return image.path!;
}

export const PickImages = async () => {
    const pickedImageResults = await Camera.pickImages({
        quality: 80,
    });
    return pickedImageResults.photos;
}