import { 
  IonContent, 
  IonHeader, 
  IonPage, 
  IonTitle, 
  IonToolbar,
  IonItemGroup,
  IonItemDivider,
  IonItem,
  IonLabel,
  useIonAlert,
  useIonLoading } from '@ionic/react';

import { Camera, CameraResultType, CameraSource, GalleryPhoto } from '@capacitor/camera';

import './Home.css';

import { useHistory } from 'react-router';

import { ImageResultsRepository } from '../utils/ImageRepository';
import { BarcodeRepository } from '../utils/BarcodeRepository';

/* Scanbot SDK Service */
import { ScanbotSDKService } from '../services/ScanbotSDKService';

import { 
  DocumentScannerConfiguration, 
  BarcodeScannerConfiguration,
  BatchBarcodeScannerConfiguration,
  MrzScannerConfiguration,
  CheckRecognizerConfiguration} from 'cordova-plugin-scanbot-sdk';

const Home: React.FC = () => {

  const history = useHistory();
  const [presentAlert] = useIonAlert();
  const [present, dismiss] = useIonLoading();

  // scan document SDK feature
  const startDocumentScanner = async () => {
  
    const configs: DocumentScannerConfiguration = {
      cameraPreviewMode: 'FIT_IN',
      interfaceOrientation: 'PORTRAIT',
      pageCounterButtonTitle: '%d Page(s)',
      multiPageEnabled: true,
      ignoreBadAspectRatio: true,
      topBarBackgroundColor: '#c8193c',
      bottomBarBackgroundColor: '#c8193c',
      // see further configs ...
    };

    if(!(ScanbotSDKService.checkLicense())) return;

    try {
      const documentScannerResults = await ScanbotSDKService.SDK.UI.startDocumentScanner({uiConfigs: configs});
    
      if (documentScannerResults.status === 'CANCELED') { return; } 

      await ImageResultsRepository.INSTANCE.addPages(documentScannerResults.pages);

      history.push("/imagepreview");

    } catch (error) {
      console.error(error);
    }
  }

  // scan barcode feature
  const scanBarcode = async () => {

    let barcodeString:string = '';

    const configs: BarcodeScannerConfiguration = {
      // Customize colors, text resources, behavior, etc..
      finderTextHint: 'Please align the barcode or QR code in the frame above to scan it.',
      interfaceOrientation: 'PORTRAIT',
      finderLineColor: '#0000ff',
      barcodeFormats: BarcodeRepository.getAcceptedTypes(), // optional filter for specific barcode types
      // see further configs ...
    };

    if(!(ScanbotSDKService.checkLicense())) return;

    try {
      const barcodeScannerResults = await ScanbotSDKService.SDK.UI.startBarcodeScanner({uiConfigs: configs});

      if(barcodeScannerResults.status == "CANCELED") return;

      barcodeScannerResults.barcodes!.forEach(barcode => {
        barcodeString += barcode.type + ' : ' + barcode.text + '\n';
      });

      presentAlert({
        header: 'Barcode Results',
        message: barcodeString,
        buttons: ['OK'],
      })

    } catch (error) {
      console.error(error);
    }
  }

  // scan batch barcode feature
  const scanBatchBarcode = async () => {

    let batchBarcodeString:string = '';

    const configs: BatchBarcodeScannerConfiguration = {
      // Customize colors, text resources, behavior, etc..
      finderTextHint: 'Please align the barcode or QR code in the frame above to scan it.',
      interfaceOrientation: 'PORTRAIT',
      finderLineColor: '#0000ff',
      barcodeFormats: BarcodeRepository.getAcceptedTypes(), // optional filter for specific barcode types
      // see further configs ...
    };

    if(!(ScanbotSDKService.checkLicense())) return;

    try {
      const batchBarcodeScannerResults = await ScanbotSDKService.SDK.UI.startBatchBarcodeScanner({uiConfigs: configs});

      if(batchBarcodeScannerResults.status == "CANCELED") return;

      batchBarcodeScannerResults.barcodes!.forEach(barcode => {
        batchBarcodeString += barcode.type + ' : ' + barcode.text + '\r\n';
      });

      presentAlert({
        header: 'Barcode Results',
        message: batchBarcodeString,
        buttons: ['OK'],
      })

    } catch (error) {
      console.error(error);
    }
  }

  // detect barcodes from a image
  const detectBarcodeFromImage = async () => {
    try {

      let barcodeResultString:string = '';

      const image = await Camera.getPhoto({
        resultType: CameraResultType.Uri,
        source: CameraSource.Photos,
      });

      const originalImageFileUri = image.path!;

      present({
        message: 'Loading...',
        spinner: 'circles'
      })

      const result = await ScanbotSDKService.SDK.detectBarcodesOnImage({ imageFileUri: originalImageFileUri });

      if(result.status == "CANCELED") return;

      result.barcodes!.forEach(barcode => {
        barcodeResultString += barcode.type + ' : ' + barcode.text + '\r\n';
      });

      dismiss();

      presentAlert({
        header: 'Barcode Results',
        message: barcodeResultString,
        buttons: ['OK'],
      })
      
    } catch (error) {
      console.error(error);
    }
  }

  // detect barcodes from multiple images
  const detectBarcodeFromImages = async () => {
    try {
      
      let barcodeResultString:string = '';
      const originalImageFileUrls:string[] = [];

      const pickedImageResults = await Camera.pickImages({
        quality: 80,
      });

      pickedImageResults.photos.forEach(photo => {
        originalImageFileUrls.push(photo.path!);
      });

      present({
        message: 'Loading...',
        spinner: 'circles'
      })

      const response = await ScanbotSDKService.SDK.detectBarcodesOnImages({ imageFilesUris: originalImageFileUrls});

      if(response.status == "CANCELED") return;

      response.results!.forEach(element => {

        element.barcodeResults.forEach(barcode => {
          barcodeResultString += barcode.type + ' : ' + barcode.text + '\r\n';
        });
      });

      dismiss();

      presentAlert({
        header: 'Barcode Results',
        message: barcodeResultString,
        buttons: ['OK'],
      })
      
    } catch (error) {
      console.error(error);
    }
  }

  // scan mrz
  /// todo => ios does not work need to check with anguler example app.
  const scanMRZ = async () => {

    try {
      let mrzResultString:string = '';

      const configs: MrzScannerConfiguration = {
        // Customize colors, text resources, behavior, etc..
        finderTextHint: 'Please hold your phone over the 2- or 3-line MRZ code at the front of your passport.',
        interfaceOrientation: 'PORTRAIT',
        // see further configs ...
      };
      
      const result = await ScanbotSDKService.SDK.UI.startMrzScanner({uiConfigs: configs});
      
      if (result.status === 'CANCELED') {
        // user has canceled the scanning operation
        return;
      }

      result.mrzResult?.fields.forEach(element => {
        mrzResultString += (element.name + " : " + element.value + "\r\n");
      });
      presentAlert({
        header: 'Barcode Results',
        message: mrzResultString,
        buttons: ['OK'],
      })

    } catch (error) {
      console.error(error);
    }
  }

  // scan check
  const scanCheck = async () => {

    try {

      const configs: CheckRecognizerConfiguration = {
        // Customize colors, text resources, behavior, etc..
        enableCameraButtonTitle: 'Enable Camera',
        interfaceOrientation: 'PORTRAIT',
        finderLineColor: '#0000ff',
        // see further configs ...
      };
      
      const checkResult = await ScanbotSDKService.SDK.UI.startCheckRecognizer({uiConfigs: configs});
      
      if (checkResult.status === 'CANCELED') {
        // user has canceled the scanning operation
        return;
      }
      
      presentAlert({
        header: 'Barcode Results',
        message: JSON.stringify(checkResult),
        buttons: ['OK'],
      })

    } catch (error) {
      console.error(error);
    }
  }

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <IonTitle>Scanbot SDK</IonTitle>
        </IonToolbar>
      </IonHeader>
      <IonContent fullscreen>

        <IonItemGroup>
          <IonItemDivider>
            <IonLabel>DOCUMENT SCAN FEATURE</IonLabel>
          </IonItemDivider>

          <IonItem onClick={async () => { await startDocumentScanner();}}>
            <IonLabel>Scan Document</IonLabel>
          </IonItem>
          <IonItem onClick={() => { history.push("/imagepreview"); }}>
            <IonLabel>View Images</IonLabel>
          </IonItem>
        </IonItemGroup>

        <IonItemGroup>
          <IonItemDivider>
            <IonLabel>DATA DETECTORS</IonLabel>
          </IonItemDivider>

          <IonItem onClick={async() => {await scanBarcode()}}>
            <IonLabel>Scan Barcode</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await scanBatchBarcode()}}>
            <IonLabel>Batch Barcode Scanner</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await detectBarcodeFromImage()}}>
            <IonLabel>Detect Barcode From Image</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await detectBarcodeFromImages()}}>
            <IonLabel>Detect Barcode From Images</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await scanMRZ()}}>
            <IonLabel>Scan MRZ</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await scanCheck()}}>
            <IonLabel>Scan Check</IonLabel>
          </IonItem>

        </IonItemGroup>

      </IonContent>
    </IonPage>
  );
};

export default Home;