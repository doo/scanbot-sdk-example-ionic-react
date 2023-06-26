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
  useIonLoading,
  isPlatform } from '@ionic/react';

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
  CheckRecognizerConfiguration,
  HealthInsuranceCardScannerConfiguration,
  TextDataScannerStep,
  DataScannerConfiguration,
  LicensePlateScannerConfiguration,
  GenericDocumentRecognizerConfiguration} from 'cordova-plugin-scanbot-sdk';
import React from "react";

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

    if(!(await ScanbotSDKService.checkLicense())) return;

    try {
      const documentScannerResults = await ScanbotSDKService.SDK.UI.startDocumentScanner({uiConfigs: configs});
    
      if (documentScannerResults.status === 'CANCELED') {
        await presentAlert({
          header: 'Error',
          message: 'Something wrong. Please try again!',
          buttons: ['OK'],
        })

        return;
      } 

      await ImageResultsRepository.INSTANCE.addPages(documentScannerResults.pages);

      history.push("/imagepreview");

    } catch (error) {
      console.error(error);
    }
  }

  // scan barcode feature
  const startBarcodeScanner = async () => {

    if(!(await ScanbotSDKService.checkLicense())) {return};

    let barcodeString:string = '';

    const configs: BarcodeScannerConfiguration = {
      // Customize colors, text resources, behavior, etc..
      finderTextHint: 'Please align the barcode or QR code in the frame above to scan it.',
      interfaceOrientation: 'PORTRAIT',
      finderLineColor: '#0000ff',
      barcodeFormats: BarcodeRepository.getAcceptedTypes(), // optional filter for specific barcode types
      // see further configs ...
    };

    try {
      const barcodeScannerResults = await ScanbotSDKService.SDK.UI.startBarcodeScanner({uiConfigs: configs});

      if(barcodeScannerResults.status == "CANCELED") {
        await presentAlert({
          header: 'Error',
          message: 'Something wrong. Please try again!',
          buttons: ['OK'],
        })

        return;
      };

      barcodeScannerResults.barcodes!.forEach(barcode => {
        barcodeString += (barcode.type + ' : ' + barcode.text + '\r\n');
      });

      await presentAlert({
        header: 'Barcode Results',
        message: barcodeString,
        buttons: ['OK'],
      })

    } catch (error) {
      console.error(error);
    }
  }

  // scan batch barcode feature
  const startBatchBarcodeScanner = async () => {

    if(!(await ScanbotSDKService.checkLicense())) return;

    let batchBarcodeString:string = '';

    const configs: BatchBarcodeScannerConfiguration = {
      // Customize colors, text resources, behavior, etc..
      finderTextHint: 'Please align the barcode or QR code in the frame above to scan it.',
      interfaceOrientation: 'PORTRAIT',
      finderLineColor: '#0000ff',
      barcodeFormats: BarcodeRepository.getAcceptedTypes(), // optional filter for specific barcode types
      // see further configs ...
    };

    try {
      const batchBarcodeScannerResults = await ScanbotSDKService.SDK.UI.startBatchBarcodeScanner({uiConfigs: configs});

      if(batchBarcodeScannerResults.status == "CANCELED") {
        await presentAlert({
          header: 'Error',
          message: 'Something wrong. Please try again!',
          buttons: ['OK'],
        })

        return;
      };

      batchBarcodeScannerResults.barcodes!.forEach(barcode => {
        batchBarcodeString += (barcode.type + ' : ' + barcode.text + '\r\n');
      });

      await presentAlert({
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

      if(!await ScanbotSDKService.checkLicense()) return

      let barcodeResultString:string = '';

      const image = await Camera.getPhoto({
        resultType: CameraResultType.Uri,
        source: CameraSource.Photos,
      });

      const originalImageFileUri = image.path!;

      await present({
        message: 'Loading...',
        spinner: 'circles'
      })

      const result = await ScanbotSDKService.SDK.detectBarcodesOnImage({ imageFileUri: originalImageFileUri });

      if(result.status == "CANCELED") {
        await presentAlert({
          header: 'Error',
          message: 'Something wrong. Please try again!',
          buttons: ['OK'],
        })

        await dismiss();
        return;
      };

      result.barcodes!.forEach(barcode => {
        barcodeResultString += barcode.type + ' : ' + barcode.text + '\r\n';
      });

      await dismiss();

      await presentAlert({
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

      if(!await ScanbotSDKService.checkLicense()) return;
      
      let barcodeResultString:string = '';
      const originalImageFileUrls:string[] = [];

      const pickedImageResults = await Camera.pickImages({
        quality: 80,
      });

      pickedImageResults.photos.forEach(photo => {
        originalImageFileUrls.push(photo.path!);
      });

      await present({
        message: 'Loading...',
        spinner: 'circles'
      })

      const response = await ScanbotSDKService.SDK.detectBarcodesOnImages({ imageFilesUris: originalImageFileUrls});

      if(response.status == "CANCELED") {
        await presentAlert({
          header: 'Error',
          message: 'Something wrong. Please try again!',
          buttons: ['OK'],
        })

        await dismiss();
        return;
      };

      response.results!.forEach(element => {

        element.barcodeResults.forEach(barcode => {
          barcodeResultString += barcode.type + ' : ' + barcode.text + '\r\n';
        });
      });

      await dismiss();

      await presentAlert({
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
  const startMRZScanner = async () => {

    try {

      if(!await ScanbotSDKService.checkLicense()) return;

      let mrzResultString:string = '';

      const configs: MrzScannerConfiguration = {
        // Customize colors, text resources, behavior, etc..
        finderTextHint: 'Please hold your phone over the 2- or 3-line MRZ code at the front of your passport.',
        interfaceOrientation: 'PORTRAIT',
        // see further configs ...
      };

      if (isPlatform('ios')) {
        const widthPx = window.screen.width;
        configs.finderWidth = widthPx * 0.9;
        configs.finderHeight = widthPx * 0.18;
      }
      
      const result = await ScanbotSDKService.SDK.UI.startMrzScanner({uiConfigs: configs});
      
      if (result.status === 'CANCELED') {
        await presentAlert({
          header: 'Error',
          message: 'Something wrong. Please try again!',
          buttons: ['OK'],
        })

        return;
      }

      result.mrzResult?.fields.forEach(element => {
        mrzResultString += (element.name + " : " + element.value + "\r\n");
      });

      await presentAlert({
        header: 'MRZ Results',
        message: mrzResultString,
        buttons: ['OK'],
      })

    } catch (error) {
      console.error(error);
    }
  }

  // perform OCR, read text from a image
  const startOCR = async () => {
    
    try {
      
      if(!await ScanbotSDKService.checkLicense()) return;

      let pages = ImageResultsRepository.INSTANCE.getPages();

      if(pages == undefined || pages.length <= 0 ){
        await presentAlert({
          header: 'No Pages to Extract Data',
          message: 'Please add a Document',
          buttons: ['OK'],
        })

        //https://scanbot.atlassian.net/browse/EPIC-2857

        return;
      }

      await present({
        message: 'Loading...',
        spinner: 'circles'
      })
      
      const ocrResult = await ScanbotSDKService.SDK.performOcr({
        images: pages.map(p => p.documentImageFileUri!),
        languages: ['en', 'de'],
        outputFormat: 'FULL_OCR_RESULT',
      });

      await dismiss();

      await presentAlert({
        header: 'OCR Results',
        message: JSON.stringify(ocrResult),
        buttons: ['OK'],
      })

    } catch (error) {
      await presentAlert({
        header: 'OCR Results',
        message: 'error',
        buttons: ['OK'],
      })
      console.error(error);
    }
  }

  // scan check
  const startCheckScanner = async () => {

    try {

      if(!await ScanbotSDKService.checkLicense()) return;

      const configs: CheckRecognizerConfiguration = {
        // Customize colors, text resources, behavior, etc..
        enableCameraButtonTitle: 'Enable Camera',
        interfaceOrientation: 'PORTRAIT',
        finderLineColor: '#0000ff',
        // see further configs ...
      };
      
      const checkResult = await ScanbotSDKService.SDK.UI.startCheckRecognizer({uiConfigs: configs});
      
      if (checkResult.status === 'CANCELED') {
        await presentAlert({
          header: 'Error',
          message: 'Something wrong. Please try again!',
          buttons: ['OK'],
        })

        return;
      }
      
      await presentAlert({
        header: 'Barcode Results',
        message: JSON.stringify(checkResult),
        buttons: ['OK'],
      })

    } catch (error) {
      console.error(error);
    }
  }

  // scan medical card
  const startEHICCardScanner = async () => {

    try {
      
      if(!await ScanbotSDKService.checkLicense()) return;

      const configs: HealthInsuranceCardScannerConfiguration = {
        // Customize colors, text resources, behavior, etc..
        finderTextHint: 'Please hold your phone over the back of your Health Insurance Card.',
        interfaceOrientation: 'PORTRAIT',
        // see further configs ...
      };
      
      const ehicResult = await ScanbotSDKService.SDK.UI.startEHICScanner({uiConfigs: configs});
      
      if (ehicResult.status === 'CANCELED') {
        await presentAlert({
          header: 'Error',
          message: 'Something wrong. Please try again!',
          buttons: ['OK'],
        })

        return;
      }

      await presentAlert({
        header: 'EHIC Results',
        message: JSON.stringify(ehicResult),
        buttons: ['OK'],
      })
      
    } catch (error)
    {
      console.error(error);
    }
  }

  // scan data
  const startDataScanner = async () => {

    try {
      
      if(!await ScanbotSDKService.checkLicense()) return; 

      const uiConfigs: DataScannerConfiguration = {
        // Customize colors, text resources, behavior, etc..
        cancelButtonTitle: 'Cancel',
        topBarBackgroundColor: '#c8193c',
        topBarButtonsColor: '#ffffff',
        finderLineColor: '#c8193c',
        interfaceOrientation: 'PORTRAIT',
        // see further configs...
      };
      
      const scannerStep: TextDataScannerStep = {
        textFilterStrategy: 'DOCUMENT',
        guidanceText: 'Place the text line in the frame to scan it',
        // an optional pattern can be used to validate scanned text and get better OCR results
        // '?' for any character, '#' for any digit, all other characters represent themselves.
        //pattern: '',
      };
      
      const dataScannerResult = await ScanbotSDKService.SDK.UI.startDataScanner({uiConfigs, scannerStep});
      
      if (dataScannerResult.status === 'CANCELED') {
        await presentAlert({
          header: 'Error',
          message: 'Something wrong. Please try again!',
          buttons: ['OK'],
        })

        return;
      }

      await presentAlert({
        header: 'Data Scanner Results',
        message: JSON.stringify(dataScannerResult),
        buttons: ['OK'],
      })
      
    } catch (error) {
      console.error(error);
    }
  }

  // license plate scanner
  const startLicensePlateScanner = async () => {
    try {
      
      if(!await ScanbotSDKService.checkLicense()) return;

      const config: LicensePlateScannerConfiguration = {
        // Customize colors, text resources, behavior, etc..
        detectorMode: 'ML_BASED',
        topBarBackgroundColor: '#c8193c',
        topBarButtonsColor: '#ffffff',
        cancelButtonTitle: 'Cancel',
        finderLineColor: '#c8193c',
        finderLineWidth: 5,
        guidanceText: 'Place the whole license plate in the frame to scan it',
        interfaceOrientation: 'PORTRAIT',
        confirmationDialogConfirmButtonFilled: true,
        // see further configs...
      };
      
      const licensePlateScannerResult = await ScanbotSDKService.SDK.UI.startLicensePlateScanner({uiConfigs: config});
      
      if (licensePlateScannerResult.status === 'CANCELED') {
        await presentAlert({
          header: 'Error',
          message: 'Something wrong. Please try again!',
          buttons: ['OK'],
        })

        return;
      }

      await presentAlert({
        header: 'License Plate Results',
        message: JSON.stringify(licensePlateScannerResult),
        buttons: ['OK'],
      })

    } catch (error) {
      console.error(error);
    }
  }

  const startGenericDocumentScanner = async () => {

    try {
      
      if(!await ScanbotSDKService.checkLicense()) return;

      const config: GenericDocumentRecognizerConfiguration = {
        // Customize colors, text resources, behavior, etc..
        shouldSavePhotoImageInStorage: true,
        // see further configs...
      };
      
      const genericDocumentRecognizerResult = await ScanbotSDKService.SDK.UI.startGenericDocumentRecognizer({uiConfigs: config});
      
      if (genericDocumentRecognizerResult.status === 'CANCELED') {
        await presentAlert({
          header: 'Error',
          message: 'Something wrong. Please try again!',
          buttons: ['OK'],
        })

        return;
      }

      await presentAlert({
        header: 'License Plate Results',
        message: JSON.stringify(genericDocumentRecognizerResult),
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
            <IonLabel>View Image Results</IonLabel>
          </IonItem>
        </IonItemGroup>

        <IonItemGroup>
          <IonItemDivider>
            <IonLabel>BarCode Detector</IonLabel>
          </IonItemDivider>

          <IonItem onClick={async() => {await startBarcodeScanner()}}>
            <IonLabel>Scan QR-/Barcode</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await startBatchBarcodeScanner()}}>
            <IonLabel>Scan Batch of Barcodes</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await detectBarcodeFromImage()}}>
            <IonLabel>Import Image & Detect Barcodes</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await detectBarcodeFromImages()}}>
            <IonLabel>Import Images & Detect Barcodes</IonLabel>
          </IonItem>

        </IonItemGroup>

        <IonItemGroup>
          <IonItemDivider>
            <IonLabel>Data Detectors</IonLabel>
          </IonItemDivider>
          <IonItem onClick={async() => {await startMRZScanner()}}>
            <IonLabel>Scan MRZ</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await startEHICCardScanner()}}>
            <IonLabel>Scan Health Insuarance Card</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await startCheckScanner()}}>
            <IonLabel>Scan Checks</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await startLicensePlateScanner()}}>
            <IonLabel>Scan License Plate (ML)</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await startOCR()}}>
            <IonLabel>Read Texts From a Document</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await startDataScanner()}}>
            <IonLabel>Scan Data</IonLabel>
          </IonItem>

          <IonItem onClick={async() => {await startGenericDocumentScanner()}}>
            <IonLabel>Scan Generic Documents</IonLabel>
          </IonItem>
        </IonItemGroup>

      </IonContent>
    </IonPage>
  );
};

export default Home;