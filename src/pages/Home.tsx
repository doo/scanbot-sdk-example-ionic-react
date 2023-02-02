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
  useIonAlert } from '@ionic/react';
import './Home.css';

import { useHistory } from 'react-router';

import { ImageResultsRepository } from '../utils/ImageRepository';
import { BarcodeRepository } from '../utils/BarcodeRepository';

/* Scanbot SDK Service */
import { ScanbotSDKService } from '../services/ScanbotSDKService';

import { 
  DocumentScannerConfiguration, 
  BarcodeScannerConfiguration} from 'cordova-plugin-scanbot-sdk';

const Home: React.FC = () => {

  const history = useHistory();
  const [presentAlert] = useIonAlert();

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
            <IonLabel>Document Scan Feature</IonLabel>
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
            <IonLabel>Barcode Scan Feature</IonLabel>
          </IonItemDivider>

          <IonItem onClick={async() => {await scanBarcode()}}>
            <IonLabel>Scan Barcode</IonLabel>
          </IonItem>
        </IonItemGroup>

      </IonContent>
    </IonPage>
  );
};

export default Home;