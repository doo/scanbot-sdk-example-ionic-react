import React from 'react';
import {
  IonContent,
  IonHeader,
  IonPage,
  IonToolbar,
  IonItemGroup,
  IonItemDivider,
  IonItem,
  IonLabel,
  useIonAlert,
  useIonLoading,
  isPlatform,
  IonTitle,
} from '@ionic/react';

import { Camera, CameraResultType, CameraSource } from '@capacitor/camera';

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
  GenericDocumentRecognizerConfiguration,
  BarcodeResultField,
  FinderDocumentScannerConfiguration,
} from 'cordova-plugin-scanbot-sdk';

const Home: React.FC = () => {
  const history = useHistory();
  const [presentAlert] = useIonAlert();
  const [present, dismiss] = useIonLoading();

  // -----------------
  // Document Scanner
  // -----------------
  const startDocumentScanner = async () => {
    if (!(await ScanbotSDKService.checkLicense())) { return; }

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
    try {
      const documentScannerResults = await ScanbotSDKService.SDK.UI.startDocumentScanner({ uiConfigs: configs });
      if (documentScannerResults.status === 'CANCELED') {
        await presentAlert({
          header: 'Information',
          message: 'Document scanner has been canceled.',
          buttons: ['OK'],
        });
        return;
      }
      await ImageResultsRepository.INSTANCE.addPages(documentScannerResults.pages);
      history.push("/imagepreview");
    }
    catch (error) {
      console.error(error);
    }
  }

  // ------------------------
  // Finder Document Scanner
  // ------------------------
  const startFinderDocumentScanner = async () => {
    if (!(await ScanbotSDKService.checkLicense())) { return; }

    const configs: FinderDocumentScannerConfiguration = {
      // Customize colors, text resources, behavior, etc..
      cameraPreviewMode: 'FILL_IN',
      interfaceOrientation: 'PORTRAIT',
      ignoreBadAspectRatio: true,
      topBarBackgroundColor: '#c8193c',
      finderEnabled: true,
      finderAspectRatio: { width: 4, height: 3 }
      // see further configs ...
    };
    try {
      const finderDocumentScannerResults = await ScanbotSDKService.SDK.UI.startFinderDocumentScanner({ uiConfigs: configs });
      if (finderDocumentScannerResults.status === 'CANCELED') {
        await presentAlert({
          header: 'Information',
          message: 'Document scanner has been canceled.',
          buttons: ['OK'],
        });
        return;
      }

      await ImageResultsRepository.INSTANCE.addPages([finderDocumentScannerResults.page]);
      history.push("/imagepreview");
    }
    catch (error) {
      console.error(error);
    }
  }

  // __________________
  // Barcode Scanner
  // __________________
  const startBarcodeScanner = async () => {
    if (!(await ScanbotSDKService.checkLicense())) { return; }

    const configs: BarcodeScannerConfiguration = {
      // Customize colors, text resources, behavior, etc..
      finderTextHint: 'Please align the barcode or QR code in the frame above to scan it.',
      interfaceOrientation: 'PORTRAIT',
      finderLineColor: '#0000ff',
      barcodeFormats: BarcodeRepository.getAcceptedTypes(), // optional filter for specific barcode types
      // see further configs ...
    };
    try {
      const barcodeScannerResults = await ScanbotSDKService.SDK.UI.startBarcodeScanner({ uiConfigs: configs });
      if (barcodeScannerResults.status === 'CANCELED') {
        await presentAlert({
          header: 'Information',
          message: 'Barcode scanner has been canceled.',
          buttons: ['OK'],
        })
        return;
      }
      let barcodeString: string = '';
      barcodeScannerResults.barcodes!.forEach(barcode => {
        barcodeString += (barcode.type + ' : ' + barcode.text + '\r\n');
      });
      await presentAlert({
        header: 'Barcode Results',
        message: barcodeString,
        buttons: ['OK'],
      })
    }
    catch (error) {
      console.error(error);
    }
  }

  // ---------------------
  // BatchBarcode Scanner
  // ---------------------
  const startBatchBarcodeScanner = async () => {
    if (!(await ScanbotSDKService.checkLicense())) { return; }

    const configs: BatchBarcodeScannerConfiguration = {
      // Customize colors, text resources, behavior, etc..
      finderTextHint: 'Please align the barcode or QR code in the frame above to scan it.',
      interfaceOrientation: 'PORTRAIT',
      finderLineColor: '#0000ff',
      barcodeFormats: BarcodeRepository.getAcceptedTypes(), // optional filter for specific barcode types
      // see further configs ...
    };
    try {
      const batchBarcodeScannerResults = await ScanbotSDKService.SDK.UI.startBatchBarcodeScanner({ uiConfigs: configs });
      if (batchBarcodeScannerResults.status === 'CANCELED') {
        await presentAlert({
          header: 'Information',
          message: 'BatchBarcode scanner has been canceled.',
          buttons: ['OK'],
        });
        return;
      }
      await BarcodeRepository.addBarcodes(batchBarcodeScannerResults.barcodes!);
      history.push("/barcoderesultview");
    }
    catch (error) {
      console.error(error);
    }
  }

  // ------------------------------
  // Detect barcodes from an image
  // ------------------------------
  const detectBarcodeFromImage = async () => {
    if (!(await ScanbotSDKService.checkLicense())) { return; }

    try {
      const image = await Camera.getPhoto({
        resultType: CameraResultType.Uri,
        source: CameraSource.Photos,
      });

      const originalImageFileUri = image.path!;
      await present({
        message: 'Detecting barcodes...',
        spinner: 'circles'
      });
      const result = await ScanbotSDKService.SDK.detectBarcodesOnImage({ imageFileUri: originalImageFileUri });

      if (result.status === 'CANCELED') {
        await dismiss();
        await presentAlert({
          header: 'Information',
          message: 'Barcode detection process canceled.',
          buttons: ['OK'],
        });
        return;
      }
      else if (result.barcodes?.length === 0) {
        await dismiss();
        await presentAlert({
          header: 'Information',
          message: 'No barcodes detected.',
          buttons: ['OK'],
        });
        return;
      }
      await dismiss();
      await BarcodeRepository.addBarcodes(result.barcodes!);
      history.push("/barcoderesultview");
    }
    catch (error) {
      console.error(error);
    }
  }

  // -------------------------------------
  // Detect barcodes from multiple images
  // -------------------------------------
  const detectBarcodeFromImages = async () => {
    if (!(await ScanbotSDKService.checkLicense())) { return; }

    try {
      const barcodes: BarcodeResultField[] = [];
      const originalImageFileUrls: string[] = [];
      const pickedImageResults = await Camera.pickImages({
        quality: 80,
      });

      pickedImageResults.photos.forEach(photo => {
        originalImageFileUrls.push(photo.path!);
      });
      await present({
        message: 'Detecting barcodes...',
        spinner: 'circles'
      });
      const response = await ScanbotSDKService.SDK.detectBarcodesOnImages({ imageFilesUris: originalImageFileUrls });
      if (response.status === 'CANCELED') {
        await dismiss();
        await presentAlert({
          header: 'Information',
          message: 'Barcode detection process canceled.',
          buttons: ['OK'],
        });
        return;
      }
      response.results!.forEach(element => {
        element.barcodeResults.forEach(barcode => {
          barcodes.push(barcode);
        });
      });
      if (barcodes?.length === 0) {
        await dismiss();
        await presentAlert({
          header: 'Information',
          message: 'No barcodes detected.',
          buttons: ['OK'],
        });
        return;
      }
      await BarcodeRepository.addBarcodes(barcodes);
      await dismiss();
      history.push("/barcoderesultview");
    }
    catch (error) {
      console.error(error);
    }
  }

  // -------------
  // MRZ scanner
  // -------------
  const startMRZScanner = async () => {
    if (!(await ScanbotSDKService.checkLicense())) { return; }

    try {
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
      const result = await ScanbotSDKService.SDK.UI.startMrzScanner({ uiConfigs: configs });
      if (result.status === 'CANCELED') {
        await presentAlert({
          header: 'Information',
          message: 'MRZ scanner canceled.',
          buttons: ['OK'],
        });
        return;
      }
      let mrzResultString: string = '';
      result.mrzResult?.fields.forEach(element => {
        mrzResultString += (element.name + " : " + element.value + "\r\n");
      });
      await presentAlert({
        header: 'MRZ Results',
        message: mrzResultString,
        buttons: ['OK'],
      });
    }
    catch (error) {
      console.error(error);
    }
  }

  // --------------
  // Check Scanner
  // --------------
  const startCheckScanner = async () => {
    if (!(await ScanbotSDKService.checkLicense())) { return; }

    try {
      const configs: CheckRecognizerConfiguration = {
        // Customize colors, text resources, behavior, etc..
        enableCameraButtonTitle: 'Enable Camera',
        interfaceOrientation: 'PORTRAIT',
        finderLineColor: '#0000ff',
        // see further configs ...
      };
      const checkResult = await ScanbotSDKService.SDK.UI.startCheckRecognizer({ uiConfigs: configs });
      if (checkResult.status === 'CANCELED') {
        await presentAlert({
          header: 'Information',
          message: 'Check scanner canceled.',
          buttons: ['OK'],
        });
        return;
      }
      await presentAlert({
        header: 'Check Result',
        message: JSON.stringify(checkResult),
        buttons: ['OK'],
      });
    }
    catch (error) {
      console.error(error);
    }
  }

  // ------------------
  // EHIC Card Scanner
  // ------------------
  const startEHICCardScanner = async () => {
    if (!(await ScanbotSDKService.checkLicense())) { return; }

    try {
      const configs: HealthInsuranceCardScannerConfiguration = {
        // Customize colors, text resources, behavior, etc..
        finderTextHint: 'Please hold your phone over the back of your Health Insurance Card.',
        interfaceOrientation: 'PORTRAIT',
        // see further configs ...
      };
      const ehicResult = await ScanbotSDKService.SDK.UI.startEHICScanner({ uiConfigs: configs });
      if (ehicResult.status === 'CANCELED') {
        await presentAlert({
          header: 'Information',
          message: 'EHIC Scanner canceled.',
          buttons: ['OK'],
        });
        return;
      }
      await presentAlert({
        header: 'EHIC Results',
        message: JSON.stringify(ehicResult),
        buttons: ['OK'],
      });
    }
    catch (error) {
      console.error(error);
    }
  }

  // -------------
  // Data Scanner
  // -------------
  const startDataScanner = async () => {
    if (!(await ScanbotSDKService.checkLicense())) { return; }

    try {
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
      const dataScannerResult = await ScanbotSDKService.SDK.UI.startDataScanner({ uiConfigs, scannerStep });
      if (dataScannerResult.status === 'CANCELED') {
        await presentAlert({
          header: 'Information',
          message: 'Data scanner canceled.',
          buttons: ['OK'],
        });
        return;
      }
      await presentAlert({
        header: 'Data Scanner Results',
        message: JSON.stringify(dataScannerResult),
        buttons: ['OK'],
      });
    }
    catch (error) {
      console.error(error);
    }
  }

  // ----------------------
  // License Plate Scanner
  // ----------------------
  const startLicensePlateScanner = async () => {
    if (!(await ScanbotSDKService.checkLicense())) { return; }

    try {
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
      const licensePlateScannerResult = await ScanbotSDKService.SDK.UI.startLicensePlateScanner({ uiConfigs: config });
      if (licensePlateScannerResult.status === 'CANCELED') {
        await presentAlert({
          header: 'Information',
          message: 'License plate scanner canceled.',
          buttons: ['OK'],
        });
        return;
      }
      await presentAlert({
        header: 'License Plate Results',
        message: JSON.stringify(licensePlateScannerResult),
        buttons: ['OK'],
      });
    }
    catch (error) {
      console.error(error);
    }
  }

  // -------------------------
  // Generic Document Scanner
  // -------------------------
  const startGenericDocumentScanner = async () => {
    if (!(await ScanbotSDKService.checkLicense())) { return; }

    try {
      const config: GenericDocumentRecognizerConfiguration = {
        // Customize colors, text resources, behavior, etc..
        shouldSavePhotoImageInStorage: true,
        // see further configs...
      };
      const genericDocumentRecognizerResult = await ScanbotSDKService.SDK.UI.startGenericDocumentRecognizer({ uiConfigs: config });
      if (genericDocumentRecognizerResult.status === 'CANCELED') {
        await presentAlert({
          header: 'Information',
          message: 'Generic document scanner canceled.',
          buttons: ['OK'],
        });
        return;
      }
      await presentAlert({
        header: 'Scanner Results',
        message: JSON.stringify(genericDocumentRecognizerResult),
        buttons: ['OK'],
      });
    }
    catch (error) {
      console.error(error);
    }
  }

  // -------------------------
  // SDK License Information
  // -------------------------
  const viewLicenseInfo = async () => {
    const result = await ScanbotSDKService.SDK.getLicenseInfo();
    await presentAlert({
      header: 'License Info',
      message: JSON.stringify(result),
      buttons: ['OK'],
    });
  }

  // -------------------------
  // OCR Confoguaration
  // -------------------------
  const viewOcrConfigs = async () => {
    const result = await ScanbotSDKService.SDK.getOcrConfigs();
    await presentAlert({
      header: 'OCR Configs',
      message: JSON.stringify(result),
      buttons: ['OK'],
    });
  }

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar color="primary">
          <IonTitle>Scanbot SDK Example</IonTitle>
        </IonToolbar>
      </IonHeader>

      <IonContent fullscreen>
        <IonItemGroup>
          <IonItemDivider>
            <IonLabel>Document Scanner</IonLabel>
          </IonItemDivider>

          <IonItem onClick={async () => { await startDocumentScanner(); }}>
            <IonLabel>Scan Document</IonLabel>
          </IonItem>
          <IonItem onClick={async () => { await startFinderDocumentScanner(); }}>
            <IonLabel>Finder Document Scanner</IonLabel>
          </IonItem>
          <IonItem onClick={() => { history.push("/imagepreview"); }}>
            <IonLabel>View Image Results</IonLabel>
          </IonItem>
        </IonItemGroup>

        <IonItemGroup>
          <IonItemDivider>
            <IonLabel>Barcode Scanner & Detector</IonLabel>
          </IonItemDivider>

          <IonItem onClick={async () => { await startBarcodeScanner() }}>
            <IonLabel>Scan QR-/Barcode</IonLabel>
          </IonItem>

          <IonItem onClick={async () => { await startBatchBarcodeScanner() }}>
            <IonLabel>Scan Batch of Barcodes</IonLabel>
          </IonItem>

          <IonItem onClick={async () => { await detectBarcodeFromImage() }}>
            <IonLabel>Import Image & Detect Barcodes</IonLabel>
          </IonItem>

          <IonItem onClick={async () => { await detectBarcodeFromImages() }}>
            <IonLabel>Import Images & Detect Barcodes</IonLabel>
          </IonItem>

        </IonItemGroup>

        <IonItemGroup>
          <IonItemDivider>
            <IonLabel>Data Detectors</IonLabel>
          </IonItemDivider>
          <IonItem onClick={async () => { await startMRZScanner() }}>
            <IonLabel>Scan MRZ</IonLabel>
          </IonItem>

          <IonItem onClick={async () => { await startEHICCardScanner() }}>
            <IonLabel>Scan Health Insurance Card</IonLabel>
          </IonItem>

          <IonItem onClick={async () => { await startCheckScanner() }}>
            <IonLabel>Scan Checks</IonLabel>
          </IonItem>

          <IonItem onClick={async () => { await startLicensePlateScanner() }}>
            <IonLabel>Scan License Plate</IonLabel>
          </IonItem>

          <IonItem onClick={async () => { await startDataScanner() }}>
            <IonLabel>Scan Data</IonLabel>
          </IonItem>

          <IonItem onClick={async () => { await startGenericDocumentScanner() }}>
            <IonLabel>Scan Generic Documents</IonLabel>
          </IonItem>
        </IonItemGroup>

        <IonItemGroup>
          <IonItemDivider>
            <IonLabel>Test Other SDK API Methods</IonLabel>
          </IonItemDivider>

          <IonItem onClick={async () => { await viewLicenseInfo(); }}>
            <IonLabel>View License Info</IonLabel>
          </IonItem>
          <IonItem onClick={async () => { await viewOcrConfigs(); }}>
            <IonLabel>View OCR Configs</IonLabel>
          </IonItem>
          <IonItem>
            <a href="https://scanbot.io" target="_blank" rel="noopener noreferrer">
              Learn More About the Scanbot SDK
            </a>
          </IonItem>
        </IonItemGroup>

      </IonContent>
    </IonPage>
  );
};

export default Home;
